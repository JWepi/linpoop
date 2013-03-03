#include	<netdb.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<netinet/in.h>
#include	<strings.h>
#include	<stdlib.h>
#include	"Client.hh"

Client::Client(const std::string &hostname, int port) : _sockfd(0), _port(port), _host(hostname.c_str())
{
	_buff = malloc(BUFF_SIZE);
	bzero(_buff, BUFF_SIZE);
	create_socket();
}

Client::~Client()
{
	free(_buff);
}

void	Client::create_socket()
{
	struct protoent	*pe;

	pe = getprotobyname("TCP");
	_sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
}

int		Client::start()
{
	struct sockaddr_in	sin;
	
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port);
	sin.sin_addr.s_addr = inet_addr(_host);
	return (connect(_sockfd, (const struct sockaddr *)&sin, sizeof(sin)));
}

int		Client::send_msg(Packet *p) const
{
	return (send(_sockfd, (char *)p->getPacket(), p->getPacketSize(), 0));
}

int		Client::recv_msg()
{
	Packet	*p;
	int		nb_read;

	nb_read = recv(_sockfd, (char *)_data, BUFF_SIZE, 0);
	if (nb_read > 0)
	{
		p = new Packet(_buff);
		if (p->getType() > 0)
			readPacketCommand(p);
		else
			std::cerr << "error : invalid packet" << std::endl;
	}
	else
		std::cerr << "error : recv failed" << std::endl;
	return (nb_read);
}

void	Client::readPacketCommand(Packet *p) const
{
	char	type;

	type = p->getType();
	switch (type)
	{
		case 1:
			client_ping(p);
			break;
		/* AJOUTER ICI TOUS LES CAS DE REQUETES A TRAITER */
	}
}
