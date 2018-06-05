// TODO: Make the file read-only to avoid any overwrite accidents while exploring the file using a host os

// TODO: what if the card doesnt conatain a MBR record, make a way that if it's only one partition without MBR it won't fail

// NOTE: some OS's read from the 2nd table of the FAT thus when there is 2 FAT's, duplicate the data written to it.

// TODO: Add upper limits for the data types that correspondes to max file capacity

// TODO: make sure that the endianess of the system doesnt affect the read/write operation to the sd (fat16 is little endian)

// TODO: the seek, read & write (low level i/o) should have a pointer and auto increments it, in mcu we need a pointer to keep memory of the offset

// To open "SUBDIR/1.TXT", just replace the fat16_open_file() with:    fat16_open_file("SUBDIR  ", "   ");
//                                                                     fat16_open_file("1       ", "TXT");      

// NOTE: memPtr is a linear incrementing counter that points to the current position of the data.
//       as the clusters assigned sequentially, no need to change memPtr

#include "util.h"
#include "fat16.h"
#include "uart.h"
#include "main_ht66f0185.h"

uint8_t fat16_buffer[FAT16_BUFFER_SIZE];
Fat16State fat16_state;
//static uint32_t memPtr, clsPtr;  // mem offset in the current cluster , current cluster value
static uint32_t file_data_addr;


// access function (I/O functions) must be provided by the user
// Provide disk access function for FAT16 library
void FAT16_seek(uint32_t offset) {
    //fseek(in, offset, SEEK_SET);
    SD_seek(offset);
}

int8_t FAT16_read(uint8_t *ptr, uint8_t bytes)
{
    //return (int8_t)fread(fat16_buffer, 1, bytes, in);
    return (int8_t)SD_get(ptr, bytes);
}

int8_t FAT16_write(uint8_t bytes)
{
    //return (int8_t)fwrite(fat16_buffer, 1, bytes, in);
}

// Initializes the library
//  1- locates the first FAT16 partition,
//  2- loads the relevant part of its boot sector to calculate values needed for operation
//  3- positions the file reading routines to the start of root directory entries
// Initialize the library - locates the first FAT16 partition,
// loads the relevant part of its boot sector to calculate
// values needed for operation, and finally positions the
// file reading routines to the start of root directory entries
int8_t FAT16_init(void)
{
    int8_t i, res;
    file_data_addr = 0;
    
    FAT16_seek(0x1BE);
        
    for(i = 0; i < 4; i++)
    {        
        res = FAT16_read(fat16_buffer, FAT16_MBR_SIZE);
        
        itoa(res, c);
        UART_PUT_STRING(c);
        UART_NEW_LINE;
        
        if(MBR_PARTITION_TYPE == 4 || MBR_PARTITION_TYPE == 6 ||
           MBR_PARTITION_TYPE == 14)
            break;
    }

    if(i == 4) // none of the partitions were FAT16
        return FAT16_ERR_NO_PARTITION_FOUND;
    
    fat16_state.fat1_start = FAT16_SECTOR_SIZE * MBR_START_SECTOR; // temporary
    
    FAT16_seek(fat16_state.fat1_start + FAT16_BOOT_OFFSET);
    FAT16_read(fat16_buffer, FAT16_BOOT_SECTOR_SIZE);
    
    if(BS_SECTOR_SIZE != FAT16_SECTOR_SIZE)
        return FAT16_ERR_INVALID_SECTOR_SIZE;


    fat16_state.fat_num = BS_NUMBER_OF_FATS;
    fat16_state.fat1_start += (BS_RESERVED_SECTORS * FAT16_SECTOR_SIZE);
    fat16_state.fat2_start = fat16_state.fat1_start + BS_NUMBER_SECTORS_PER_FAT * FAT16_SECTOR_SIZE;
    
    fat16_state.root_start = fat16_state.fat1_start + BS_NUMBER_SECTORS_PER_FAT * BS_NUMBER_OF_FATS * FAT16_SECTOR_SIZE;
    
    fat16_state.data_start = fat16_state.root_start + BS_ROOT_DIR_ENTRIES * FAT16_FE_SIZE;

    fat16_state.sectors_per_cluster = BS_SECTORS_PER_CLUSTER;
    
    //fat16_state.data_sectors = BS_SECTORS_ON_PARTITION - (BS_HIDDEN_SECTORS + (BS_NUMBER_SECTORS_PER_FAT*BS_NUMBER_OF_FATS) + ((BS_ROOT_DIR_ENTRIES*FAT16_FE_SIZE) / FAT16_SECTOR_SIZE) + BS_RESERVED_SECTORS);

    //fat16_state.data_clusters = (fat16_state.data_sectors / BS_SECTORS_PER_CLUSTER) + 1;
    
    // Prepare for fat16_open_file(), cluster is not needed
    //fat16_state.file_left = BS_ROOT_DIR_ENTRIES * FAT16_FE_SIZE;
    fat16_state.file_left = 0x00;
    fat16_state.cluster_left = 0xFFFFFFFF; // avoid FAT lookup with root dir
           
    FAT16_seek(fat16_state.root_start);

    return 0;
}


// MOVES THROUGH THE ENTRIES TO FIND THE REQUIRED FILE. stops at the start of the file (first cluster).
// NOTE: if the file name is less than 8 chars., the rest is padded with spaces. so, you need to make sure in the app
//       that the filename is  padded with spaces if needed.

// Assumes we are at the beginning of a directory. so, we must set the address in init() to the root directory
// and fat16_state.file_left is set to amount of file entries. Reads on until a given file is found,
// or no more file entries are available.
int8_t FAT16_open_file(int8_t *filename, int8_t *ext)
{  
    int8_t i, bytes;

    do {
        bytes = FAT16_read_file(FAT16_FE_SIZE);
        
        if(bytes < FAT16_FE_SIZE)
            return FAT16_ERR_FILE_READ;

        for(i=0; i<8; i++) // we don't have memcmp on a MCU...
            if(FE_FILE_NAME[i] != filename[i])
                break;        
        if(i < 8) // not the filename we are looking for
            continue;
        
        for(i=0; i<3; i++) // we don't have memcmp on a MCU...
            if(FE_EXT[i] != ext[i])
                break;
        if(i < 3) // not the extension we are looking for
            continue;

        // Initialize reading variables
        fat16_state.cluster = FE_STARTING_CLUSTER;
        fat16_state.cluster_left = fat16_state.sectors_per_cluster * 512;
        
        if(FE_FILE_NAME[0] == 0x2E || FE_ATTRIBUTES & 0x10)
        {   // directory
            // set file size so large that the file entries
            // are not limited by it, but by the sectors used
            fat16_state.file_left = 0xFFFFFFFF;
        } else {
            fat16_state.file_left = FE_FILE_SIZE;
        }
        
        // Go to first cluster
        FAT16_seek(fat16_state.data_start + (fat16_state.cluster-2) * 
            fat16_state.sectors_per_cluster * 512);
        return 0;
    } while(fat16_state.file_left > 0);
    
    return FAT16_ERR_FILE_NOT_FOUND;
}

int8_t FAT16_read_file(int8_t bytes)
{
    // reads bytes from the current location (file or entries), returns the number of bytes read
    // it is used in the app. in a loop to keep reading the bytes of the file until it is consumed.

    if(fat16_state.file_left == 0)
        return 0;
    
    if(fat16_state.cluster_left == 0)
    {
        // search the FAT for the next cluster
        FAT16_seek(fat16_state.fat1_start + fat16_state.cluster + fat16_state.cluster);
        FAT16_read(fat16_buffer, 2);

        fat16_state.cluster = FAT16_ushort[0];
        fat16_state.cluster_left = fat16_state.sectors_per_cluster * 512;
        
        if(fat16_state.cluster == 0xFFFF)
        {
            // end of cluster chain
            fat16_state.file_left = 0;
            return 0;
        }
            
        // Go to cluster
        FAT16_seek(fat16_state.data_start + (fat16_state.cluster-2) * 
            fat16_state.sectors_per_cluster * 512);
    }

    // dont read out of the boundaries
    if(bytes > fat16_state.file_left)
        bytes = fat16_state.file_left;
    if(bytes > fat16_state.cluster_left)
        bytes = fat16_state.cluster_left;
        
    bytes = FAT16_read(fat16_buffer, bytes);
    
    fat16_state.file_left -= bytes;
    fat16_state.cluster_left -= bytes;
    
    return bytes;
}

#ifdef _WRITE

// TODO: add a feature that the user of the jig has to enter the time&date and use those entries to calculate the time&date for the created file.
// TODO: this impelementation uses a fully free sd card, it uses the first cluster of the data area without any checking.
// NOTE: must enter the filename padded with spaces, UPPERCASE

// returns 0 for correct operation, non-zero for error.

int8_t FAT16_create_file(int8_t *filename, int8_t *ext)
{
    int8_t bytes_read;
    uint8_t tmp_buffer[FAT16_BUFFER_SIZE];
    uint32_t i;

    FAT16_seek(fat16_state.root_start + FAT16_CREATE_FILE_ROOT_OFFSET);
    bytes_read = FAT16_read(fat16_buffer, FAT16_FE_SIZE);
    if(bytes_read < FAT16_FE_SIZE)
        return FAT16_ERR_FILE_CREATE;
        
    // check if the file already exist, or the sd card isn't properly formatted
    if (FE_FILE_NAME[0] == filename[0])
    {
        // read the mem pointer & cluster values
        fat16_state.cluster = FE_STARTING_CLUSTER;

        // as it is allocated dynamically, read it from the root entry
        fat16_state.file_left = FE_FILE_SIZE;

        fat16_state.cluster += (fat16_state.file_left / (FAT16_SECTOR_SIZE * fat16_state.sectors_per_cluster));
        
        // bytes left in the current cluster, cluster assumed to be > 2
        fat16_state.cluster_left = ((fat16_state.cluster-2) * fat16_state.sectors_per_cluster * FAT16_SECTOR_SIZE) - fat16_state.file_left;

        file_data_addr = fat16_state.data_start + (FE_STARTING_CLUSTER-2) * fat16_state.sectors_per_cluster * FAT16_SECTOR_SIZE;

        return FAT16_FILE_EXIST;
    }
    // NOTE: removed to enable overwrite of existing files, thus if there is a file in this location by accident it will overwrite it.
    //else if (FE_FILE_NAME[0] != filename[0] && FE_FILE_NAME[0] != 0) return FAT16_ERR_FILE_CREATE;


    // create the root entry
    // found the un-used entry, occupy it
    for(i = 0; i < 8; i++)
        FE_FILE_NAME[i] = filename[i];
    
    for(i = 0; i < 3; i++)
        FE_EXT[i] = ext[i];

    FE_ATTRIBUTES = 0x20;
    FE_STARTING_CLUSTER = 0x0003;
    //temp
    FE_FILE_SIZE = 0x00;

    FAT16_seek(fat16_state.root_start + FAT16_CREATE_FILE_ROOT_OFFSET);
    FAT16_write(FAT16_FE_SIZE);

    // Set state variables
    fat16_state.cluster = FE_STARTING_CLUSTER;
    fat16_state.cluster_left = fat16_state.sectors_per_cluster * FAT16_SECTOR_SIZE;

    fat16_state.file_left = 0x00;

    // the location of the start address of the file in the data area
    file_data_addr = fat16_state.data_start + (FE_STARTING_CLUSTER-2) * fat16_state.sectors_per_cluster * FAT16_SECTOR_SIZE;

    if (fat16_state.fat_num == 2)
    {
        FAT16_seek(fat16_state.fat1_start + fat16_state.cluster + fat16_state.cluster);
        FAT16_ushort[0] = 0xffff;
        FAT16_write(2);

        FAT16_seek(fat16_state.fat2_start + fat16_state.cluster + fat16_state.cluster);
        FAT16_ushort[0] = 0xffff;
        FAT16_write(2);
    }
    else if (fat16_state.fat_num == 1)
    {
        FAT16_seek(fat16_state.fat1_start + fat16_state.cluster + fat16_state.cluster);
        FAT16_ushort[0] = 0xffff;
        FAT16_write(2);
    }
        
    return 0;
}


int8_t FAT16_write_file(int8_t bytes)
{
    uint8_t i;

    // TODO: overwrite the file from the start when EOF is reached.
    //if(fat16_state.file_left == 0)  return FAT16_END_OF_FILE;

    // go to the next location to write to
    FAT16_seek(file_data_addr + fat16_state.file_left);
    bytes = FAT16_write(bytes);
    
    fat16_state.file_left += bytes;
    
    if (fat16_state.cluster_left < (uint32_t)bytes) {fat16_state.cluster_left = 0; bytes = bytes - fat16_state.cluster_left;}
    else fat16_state.cluster_left -= bytes;

    if(fat16_state.cluster_left == 0)
    {
        // set the FAT to the next cluster
        FAT16_ushort[0] = (fat16_state.cluster)+1;
        FAT16_ushort[1] = 0xffff;

        if (fat16_state.fat_num == 2)
        {
            FAT16_seek(fat16_state.fat1_start + fat16_state.cluster + fat16_state.cluster);
            FAT16_write(4);
            FAT16_seek(fat16_state.fat2_start + fat16_state.cluster + fat16_state.cluster);
            FAT16_write(4);
        }
        else if (fat16_state.fat_num == 1)
        {
            FAT16_seek(fat16_state.fat1_start + fat16_state.cluster + fat16_state.cluster);
            FAT16_write(4);
        }
        
        fat16_state.cluster++;
        fat16_state.cluster_left = (fat16_state.sectors_per_cluster * 512) - bytes;
    }

    // write the current cluster & file size into the root entry
    FE_FILE_SIZE = fat16_state.file_left;
    *(uint32_t *)((void *)fat16_buffer) = FE_FILE_SIZE;
    FAT16_seek(fat16_state.root_start + FAT16_FILE_SIZE_ENTRY_OFFSET);
    FAT16_write(4);

    return bytes;
}

#endif