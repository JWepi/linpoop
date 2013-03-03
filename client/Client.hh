#ifndef	CLIENT_H_
#define	CLIENT_H_

#include	<iostream>
#include	<string>
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
		int		recv_msg();
		void	readPacketCommand(Packet *p) const;
		/* requetes en reponse a une requete provenant du serveur */
		int		client_ping(Packet *p);
		/* requetes autonomes lancees independamment */
		int		create_account(char *login, char *pw);
	private:
		int			_sockfd;
		int			_port;
		const char	*_host;
		void		*_buff;
};

#endif
