#include	"Packet.hh"
#include	"Client.hh"

int	main()
{
	Packet *p = new Packet(1,0,0,"roger");
	Client *c = new Client("219.242.126.118", 8008);
	c->send_msg(p);
	while (1);
	return (0);
}
