#include <iostream>
#include <libusb.h>
#include <stdio.h>
#include <cstring>

using namespace std;

	 // g++ test.cpp `pkg-config --libs --cflags libusb-1.0`

void printdev(libusb_device *dev); //prototype of the function

int main() 
{
	libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    ssize_t cnt; //holding number of devices in list
    r = libusb_init(&ctx); //initialize a library session
    if(r < 0) 
    {
        cout<<"Init Error "<<r<<endl; //there was an error
        return 1;
    }
	libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
	cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
	if(cnt < 0) 
	{
	    cout<<"Get Device Error"<<endl; //there was an error
	}
	cout<<cnt<<" Devices in list."<<endl; //print total number of usb devices
	ssize_t i; //for iterating through the list
	for(i = 0; i < cnt; i++) 
	{
		printdev(devs[i]);
	}
	libusb_free_device_list(devs, 1); //free the list, unref the devices in it8
	libusb_exit(ctx); //close the session
	return 0;
}
	 
 void printdev(libusb_device *dev) 
{
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) 
    {
        cout<<"failed to get device descriptor"<<endl;
        return;
    }
    printf("Device Class: %02x ", (int)desc.bDeviceClass);
    libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);
    const libusb_interface * inter = &config->interface[0];
    const libusb_interface_descriptor * interdesc = &inter->altsetting[0];
    printf("Device Class from interface descriptor: %02x ", interdesc->bInterfaceClass);
    libusb_free_config_descriptor(config);
    printf("VendorID: %d ", desc.idVendor);
    printf("ProductID: %d ", desc.idProduct); 

    // serial number 
    libusb_device_handle * dev_handle;
    libusb_open(dev, &dev_handle);
	unsigned char manufacturer[200];
	libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer, manufacturer, 200);
	printf("  Manufacturer: %s ", manufacturer);
	unsigned char serialnumber[200];
	libusb_get_string_descriptor_ascii(dev_handle, desc.iSerialNumber, serialnumber, 200);
	printf("    Serial Number:  %s\n", serialnumber);
	libusb_close(dev_handle);

	
} 