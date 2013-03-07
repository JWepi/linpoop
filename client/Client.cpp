#include	<netdb.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<arpa/inet.h>
#include	<netinet/in.h>
#include	<strings.h>
#include	<stdlib.h>
#include	"Client.hh"
#include	"Packet.hh"
#include	"dataBuilder.hh"

int		Client::_id = 0;

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
				c->client_ping();
				break;
			case 3:
				Databuilder	d(p->getData());
				c->receive_answer_create_account(&d);
				break;
				/* AJOUTER ICI TOUS LES CAS DE REQUETES A TRAITER */
		}
	}
	return (NULL);
}

void	Client::client_ping()
{
	Packet	p(1, _id, 1, "");

	send_msg(&p);
}

void	Client::create_account(char *login, char *pw)
{
	Databuilder	d;
	std::string	result;

	d.setItem("nick", login);
	d.setItem("pwd", pw);
	result = d.build();

	Packet	p(2, _id, 1, result.c_str());
	send_msg(&p);
	_login = login;
	_pw = pw;
}

int		Client::receive_answer_create_account(Databuilder *d)
{
	int	ans;

	ans = d->getIntItem("answer");
	if (!ans)
	{
		_login = NULL;
		_pw = NULL;
	}
	return (ans);
}

int		Client::connect_account()
{
	Databuilder	d;
	std::string	data;

	d.setItem("pwd", _pw);
	data = d.build();
	if (_login && _pw)
	{
		Packet	p(4, _id, 1, data.c_str());
		send_msg(&p);
		return (1);
	}
	else
		return (0);
}

int		Client::receive_answer_connect_account(Databuilder *d)
{
/*	int	ans;

	ans = d->getIntItem("User");
	if (!ans)
	{
		_login = NULL;
		_pw = NULL;
	}
	return (ans);*/
}

void	Client::send_friend_request(int id)
{
	Packet	p(6, _id, id, "");

	send_msg(&p);
}

void	Client::answer_friend_request(int id, int answer)
{
	Databuilder	d;
	std::string	data;

	d.setItem("answer", answer);
	data = d.build();
	Packet	p(7, _id, id, data.c_str());
	send_msg(&p);
}

void	Client::receive_friend_request(int id)
{

}

void	Client::receive_answer_friend_request(int id)
{

}

void	Client::send_message_to_user(int id, std::string &msg)
{
	Databuilder	d;
	std::string	data;

	d.setItem("msg", msg);
	data = d.build();
	Packet	p(9, _id, id, data.c_str());
	send_msg(&p);
}

void	Client::receive_message_from_user(int id)
{

}

void	Client::send_message_to_group(int id, std::string &msg)
{
	Databuilder	d;
	std::string	data;

	d.setItem("msg", msg);
	data = d.build();
	Packet	p(11, _id, id, data.c_str());
	send_msg(&p);
}

void	Client::receive_message_from_group(int id)
{

}

void	Client::update_status(std::string &status)
{
// ASK DAVID
	Databuilder	d;
	std::string	data;

	d.setItem("status", status);
	data = d.build();
	Packet	p(15, _id, 1, data.c_str());
	send_msg(&p);
}

void	Client::send_file(int id, std::string &file_name)
{
	Databuilder	d;
	std::string	data;

	d.setItem("name", file_name);
	data = d.build();
	Packet	p(16, _id, 1, data.c_str());
	send_msg(&p);
}

void	Client::accept_file(int id, int answer)
{
	Databuilder	d;
	std::string	data;

	d.setItem("answer", answer);
	data = d.build();
	Packet	p(17, _id, id, data.c_str());
	send_msg(&p);
}

void	Client::receive_file(int id, char *file_name)
{

}

/*void	Client::receive_answer_file(Databuilder *d)
{

}*/
