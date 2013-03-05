#include	<netdb.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<netinet/in.h>
#include	<strings.h>
#include	<stdlib.h>
#include	"Client.hh"
#include	"Packet.hh"

Client::Client(const std::string &hostname, int port) : _sockfd(0), _port(port), _host(hostname.c_str())
{
	_buff = malloc(BUFF_SIZE);
	bzero(_buff, BUFF_SIZE);
	create_socket();
	start();
	pthread_create(&_t, NULL, &Client::readServer, this);
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
	int	ans;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port);
	sin.sin_addr.s_addr = inet_addr(_host);
	ans = connect(_sockfd, (const struct sockaddr *)&sin, sizeof(sin));
	if (ans != 0)
		std::cerr << "error : connect failed" << std::endl;
	return (ans);
}

int		Client::send_msg(Packet *p) const
{
	int	nb_send;

	std::cout << "Sending packet" << std::endl;
	nb_send = send(_sockfd, (char *)p->getPacket(), p->getPacketSize(), 0);
	if (nb_send == -1)
		std::cerr << "error : send failed" << std::endl;
	else
		std::cout << "Packet sent" << std::endl;
	return (nb_send);
}

Packet		*Client::recv_msg()
{
	Packet	*p;
	int		nb_read;

	nb_read = recv(_sockfd, (char *)_buff, BUFF_SIZE, 0);
	if (nb_read > 0)
	{
		std::cout << "Message received of length " << nb_read << std::endl;
		p = new Packet(_buff);
		if (p->getType() < 0)
			std::cerr << "error : invalid packet" << std::endl;
	}
	else
		std::cerr << "error : recv failed" << std::endl;
	return (p);
}

void	*Client::readServer(void *arg)
{
	char	type;
	Packet	*p;
	Client	*c = (Client *)arg;

	std::cout << "thread created" << std::endl;
	while (1) 
	{
		p = c->recv_msg();
		type = p->getType();
		switch (type)
		{
			case 1:
				c->client_ping(p);
				break;
				/* AJOUTER ICI TOUS LES CAS DE REQUETES A TRAITER */
		}
	}
	return (NULL);
}

int		Client::client_ping(Packet *p)
{
	std::cout << "ping recu" << std::endl;
}

int		Client::create_account(char *login, char *pw)
{

}
