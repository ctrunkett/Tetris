
#include "io_expander.h"

// private method
static i2c_status_t io_expander_wait_for_write(void)
{
  
  i2c_status_t status;
  
  if( !i2cVerifyBaseAddr(IO_EXPANDER_I2C_BASE) )
  {
    return  I2C_INVALID_BASE;
  }

  // Set the I2C address to be the EEPROM and in Write Mode
  status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);

  // Poll while the device is busy.  The  MCP24LC32AT will not ACK
  // writing an address while the write has not finished.
  do 
  {
    // The data we send does not matter.  This has been set to 0x00, but could
    // be set to anything
    status = i2cSendByte( IO_EXPANDER_I2C_BASE, 0x00, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
    
    // Wait for the address to finish transmitting
    while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {};
    
    // If the address was not ACKed, try again.
  } while (I2CMasterAdrAck(IO_EXPANDER_I2C_BASE) == false);

  return  status;
}

//*****************************************************************************
// Writes a single byte of data out to the  MCP24LC32AT EEPROM.  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    address:    16-bit address of the byte being written.  Only the lower
//                12 bits is used by the EEPROM
//
//    data:       Data written to the EEPROM.
//
// Returns
// I2C_OK if the byte was written to the EEPROM.
//*****************************************************************************
void io_expander_write_reg
(
  uint8_t  reg,
  uint8_t  data
)
{
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {};

  //==============================================================
  // Set the I2C address to be the EEPROM
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
	if(status != I2C_OK){
		return;
	}
  
  // If the EEPROM is still writing the last byte written, wait
	io_expander_wait_for_write();
  
  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE	
  //==============================================================
	i2cSendByte(
     IO_EXPANDER_I2C_BASE,
     reg,
     I2C_MCS_START | I2C_MCS_RUN
	);	
	if(status != I2C_OK){
		return;
	}

	i2cSendByte(
     IO_EXPANDER_I2C_BASE,
     data,
     I2C_MCS_RUN | I2C_MCS_STOP
	);	
	if(status != I2C_OK){
		return;
	}
  return;
}


uint8_t io_expander_read_reg(uint8_t reg) {
	uint8_t result;
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(IO_EXPANDER_I2C_BASE)) {};

  // If the EEPROM is still writing the last byte written, wait
  io_expander_wait_for_write();

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Write Mode
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
	if(status != I2C_OK){
		return status;
	}

  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE
  //==============================================================
	i2cSendByte(
     IO_EXPANDER_I2C_BASE,
     reg,
     I2C_MCS_START | I2C_MCS_RUN
	);	
	if(status != I2C_OK){
		return status;
	}



  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Read Mode
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_READ);

  //==============================================================
  // Read the data returned by the EEPROM
	// ADD CODE
  //==============================================================
  i2cGetByte(
     IO_EXPANDER_I2C_BASE,
     &result,
     I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP
	);	
  return result;

}

//*****************************************************************************
// Read the number of active touch points.
//*****************************************************************************
uint8_t io_expander_read_button_poll(int DIR_BTN_PIN)
{
  // ADD CODE
	uint8_t data;
	if ( DIR_BTN_PIN == DIR_BTN_UP_PIN )  {
		data = io_expander_read_reg(MCP23017_GPIOB_R);
		return data & 0X01;
	}
	else if ( DIR_BTN_PIN == DIR_BTN_DOWN_PIN ) {
		data = io_expander_read_reg(MCP23017_GPIOB_R);
		return data & 0X02;
	}
	else if ( DIR_BTN_PIN == DIR_BTN_LEFT_PIN ) {
		data = io_expander_read_reg(MCP23017_GPIOB_R);
		return data & 0X04;
	}
	else if ( DIR_BTN_PIN == DIR_BTN_RIGHT_PIN ) {
		data = io_expander_read_reg(MCP23017_GPIOB_R);
		return data & 0X08;
	}
	
	return -1;

} 

void toggle_LEDs(void) {
	uint8_t static LED_ON = 0x00;
	LED_ON = ~LED_ON;
	io_expander_write_reg(MCP23017_GPIOA_R, LED_ON);
}
//void io_expander_write_reg(uint8_t reg, uint8_t data) { return; }
//*****************************************************************************
// Test the io_expander
//*****************************************************************************
bool io_expander_init(void)
{
  //==============================
  // Configure I2C GPIO Pins
  //==============================  
  if(gpio_enable_port(IO_EXPANDER_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PCTL_M, IO_EXPANDER_I2C_SCL_PIN_PCTL) == false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PCTL_M, IO_EXPANDER_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
	
	// DOESN'T WORK YET NEED TO SET IM MASK IN FUNCTION
//	if ((gpio_config_falling_edge_irq(IO_EXPANDER_GPIO_BASE, DIR_BTN_UP_PIN | DIR_BTN_DOWN_PIN | DIR_BTN_LEFT_PIN | DIR_BTN_RIGHT_PIN)== false)) {
//		return false;
//	}
  
  
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(I2C1_BASE)!= I2C_OK)
  {
    return false;
  }
	
	
	//mcp23017_set_addr(IO_EXPANDER_GPIO_BASE, MCP23017_IODIRA_R); // SET DIRECTION BITS TO OUTPUT
	io_expander_write_reg(MCP23017_IODIRA_R, 0x00);
	
	//toggle_LEDs();
	
	
	io_expander_write_reg(MCP23017_IODIRB_R, 0xFF); // set as input
	//io_expander_write_reg(MCP23017_GPINTENB_R, 0xFF); // generate interrupts
	io_expander_write_reg(MCP23017_GPPUB_R, 0xFF); // set pull up resistor

  // Send the IODIRA Address
  //i2cSendByte( I2C_BASE, 0x00, I2C_MCS_START | I2C_MCS_RUN);

  // Set PortA to be outputs
  //i2cSendByte( I2C_BASE, 0x00, I2C_MCS_RUN | I2C_MCS_STOP);
	
	// SET PULL UP RESISTORS
	
  
  return true;
  
} 

