/* uses libusb version 0.1.10a found at http:⁄⁄libusb.sourceforge.net */

#include </usr/include/libusb-1.0/libusb.h>

#define VENDOR_ID  0x0DE7
#define PRODUCT_ID 0x0191

#define CANT_SEND -1
#define CANT_READ -2


static struct usb_device *find_U401( struct usb_bus *bus )
    {

    struct usb_device *dev;

    // look through all busses
    for ( ; bus; bus = bus->next )
        {
        // look at every device
        for ( dev = bus->devices; dev; dev = dev->next )
            {
            // match to known IDs
            if ( dev->descriptor.idVendor == VENDOR_ID && dev->descriptor.idProduct == PRODUCT_ID )
                {
                return dev;
                }
            }
        }
    return NULL;
}




void buffer_set( char *buf, int a, int b, int c, int d, int e, int f, int g, int h )
{
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = d;
    buf[4] = e;
    buf[5] = f;
    buf[6] = g;
    buf[7] = h;
}




int send_command( struct usb_dev_handle *handle, char *command, int comLen, int resLen )
{

    int ret = usb_control_msg( handle, 0x21, 9, 0x0200, 0, command, comLen, 5000 );

    // check that the send was successful
    if ( ret != comLen )
        return CANT_SEND;

    // does the command expect a result?
    if ( resLen > 0 )
        {
        ret = usb_bulk_read( handle, 0x81, command, resLen, 5000 );
        if ( ret != resLen )
            return CANT_READ;

        }

    return ret;

}




int main()
{

    int busses, devices, ret, portA, portB;
    struct usb_bus *bus_list;
    struct usb_device *dev = NULL;
    struct usb_dev_handle *handle;
    char buffer[8];


    // initialize the usb system
    usb_init();
    busses = usb_find_busses(); // update info on busses
    devices = usb_find_devices(); // update info on devices
    bus_list = usb_get_busses(); // get actual bus objects


    if ( ( dev = find_U401(bus_list) ) == NULL )
        return -1; // failure to find

    if ( ( handle = usb_open(dev) ) == NULL || usb_claim_interface( handle, 0 ) )
        return -1; // failure to open

    if ( usb_set_configuration(handle, 1) )
        return -1;


    // initialize the ports (A & B) as input
    buffer_set( buffer, 0, 0, 0, 0, 0, 0, 0, 0 );
    ret = send_command( handle, buffer, 8, 0 );

    if ( ret != 8 )
        return -1;


    // read port A
    buffer_set( buffer, 0x05, 0, 0, 0, 0, 0, 0, 0 );
    ret = send_command( handle, buffer, 8, 8 );

    if ( ret != 8 )
        return -1; // report error

    // print out port A value
    printf( “Port A = %d\n”, buffer[1] & 0xFF );

    // read port B
    buffer_set( buffer, 0x06, 0, 0, 0, 0, 0, 0, 0 );
    ret = send_command( handle, buffer, 8, 8 );

    if ( ret != 8 )
        return -1; // report error

    // print out port B value
    printf( “Port B = %d\n”, buffer[1] & 0xFF );


    if ( usb_release_interface(handle, 0) || usb_close(handle) )
        return -1; // report error

    return 0; // success
}
