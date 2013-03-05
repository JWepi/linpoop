#ifndef	CLIENT_H_
#define	CLIENT_H_

#include	<iostream>
#include	<string>
#include	<pthread.h>
#include	"Packet.hh"

#define	BUFF_SIZE	1000

class	Client
{
	public:
		Client(const std::string &hostname, int port);
		~Client();
		void	create_socket();
		int		start();
		int		send_msg(Packet *p) const;
		Packet	*recv_msg();
		static void	*readServer(void *arg);
		int		client_ping(Packet *p);
		int		create_account(char *login, char *pw);
	private:
		int			_sockfd;
		int			_port;
		const char	*_host;
		void		*_buff;
		pthread_t	_t;
};

#endif
