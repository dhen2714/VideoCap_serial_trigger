#include <VideoCap.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
    VideoCapture leopard_camera;
    Frame frame;

    asio::io_service io;
	asio::serial_port port(io);
 
	port.open("/dev/ttyUSB0");
	port.set_option(asio::serial_port_base::baud_rate(115200));
    port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
 
	char c;
    int retval = 0;
    int write_count = 0;
 
	// Read 1 character into c, this will block
	// forever if no character arrives.
    cout << "LUL" << endl;

    while (1) {
	    asio::read(port, asio::buffer(&c,1));

        if (c == 'a')
            cout << "YES THIS WORKS" << endl;
            retval = leopard_camera.read(frame);

            if (retval) {
                struct timeval tv;
                std::string fName;
                long ts;

                tv = frame.timestamp;
                ts = tv.tv_sec*1e6 + tv.tv_usec;
                fName = std::to_string(ts) + "_" + std::to_string(write_count) + ".pgm";
                cv::imwrite(fName, frame.image);
            }

            write_count++;
            cout << write_count << endl;
    }

	port.close();
    leopard_camera.release();

    return 0;
}
