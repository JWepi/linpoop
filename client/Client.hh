#ifndef	CLIENT_H_
#define	CLIENT_H_

#include	<iostream>
#include	<string>
#include	<pthread.h>
#include	"Packet.hh"
#include	"dataBuilder.hh"

#define	BUFF_SIZE	1000

class	Client
{
	public:
		Client(const std::string &hostname, int port);
		~Client();
		void	create_socket();
		int		start();
		/* Fonctions de communication avec le serveur */
		int		send_msg(Packet *p) const;
		Packet	*recv_msg();
		/* ------------------------------------------ */
		static void	*readServer(void *arg);
		void	client_ping();
		void	create_account(char *login, char *pw);
		int		receive_answer_create_account(Databuilder *d);
		int		receive_answer_connect_account(Databuilder *d);
		int		connect_account();
		void	send_friend_request(int id);
		void	answer_friend_request(int id, int answer);
		void	receive_friend_request(int id);
		void	receive_answer_friend_request(int id);
		void	send_message_to_user(int id, std::string &msg);
		void	receive_message_from_user(int id);
		void	send_message_to_group(int id, std::string &msg);
		void	receive_message_from_group(int id);
		void	update_status(std::string &status);
		void	send_file(int id, std::string &file_name);
		void	accept_file(int id, int answer);
		void	receive_file(int id, char *file_name);
	private:
		int			_sockfd;
		int			_port;
		const char	*_host;
		void		*_buff;
		pthread_t	_t;
		static int	_id;
		char		*_login;
		char		*_pw;
};

#endif
