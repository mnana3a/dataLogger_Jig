#ifndef __PORT_H
#define __PORT_H

/*******************************************************/
// Inputs
// analog[0:1]
#define AN0                            PIN0
#define AN1                            PIN1
/*******************************************************/
// Outputs
// sys Indication LED
#define SYS_INDICATION_DDR             GPIO_DDRC
#define SYS_INDICATION_PORT            GPIO_PORTC
#define SYS_INDICATION_PIN             PIN2
// Buck Relay
#define BUCK_RELAY_DDR                 GPIO_DDRB
#define BUCK_RELAY_PORT                GPIO_PORTB
#define BUCK_RELAY_PIN                 PIN5
// Boost Relay
#define BOOST_RELAY_DDR                GPIO_DDRB
#define BOOST_RELAY_PORT               GPIO_PORTB
#define BOOST_RELAY_PIN                PIN4
/*******************************************************/

#endif

