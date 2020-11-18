#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT_ID	8800
#define SIZE	400

int main(void)
{
	int i;

			int sock_fd, client_sockfd;
				struct sockaddr_in server_addr, client_addr;
					int addr_len;
						char black_list[] = "Get out";
							char welcome[] = "Welcome to connect the server";
								char buf[SIZE];
									char ch;
										char direct_name[SIZE];
											FILE *fp;
												int n;

													sock_fd = socket(AF_INET, SOCK_STREAM, 0);

														server_addr.sin_family = AF_INET;
															server_addr.sin_port = htons(PORT_ID);
																server_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("10.25.134.199");
																	bind(sock_fd, (struct sockaddr *)&(server_addr), sizeof(struct sockaddr));

																		listen(sock_fd, 1);

																			addr_len = sizeof(struct sockaddr);

																				while(1)
																					{
																							printf("Server is waiting for client to connect:\n");
																									client_sockfd = accept(sock_fd, (struct sockaddr *)&client_addr, &addr_len);

																											printf("Client IP = %s\n", inet_ntoa(client_addr.sin_addr));
																													send(client_sockfd, welcome, sizeof(welcome), 0);

																															recv(client_sockfd, buf, sizeof(buf), 0);
																																	printf("Receive file %s from client, do you want to save it?(Y/N)", buf);

																																			ch = getchar();
																																					if(ch != 'Y')
																																							{
																																										send(client_sockfd, &ch, 1, 0);
																																													printf("Sorry\n");
																																																close(client_sockfd);
																																																			continue;
																																																					}
																																																							else
																																																									{
																																																												send(client_sockfd, &ch, 1, 0);
																																																															printf("Please enter directory and filename that you want to save:\n");
																																																																		scanf("%s", direct_name);
																																																																					if((fp = fopen(direct_name, "ab+")) == NULL)
																																																																								{
																																																																												perror("fopen");
																																																																																close(client_sockfd);
																																																																																				continue;
																																																																																							}
																																																																																										memset(buf, '\0', sizeof(buf));
																																																																																													while(1)
																																																																																																{
																																																																																																				n = recv(client_sockfd, buf, 1, 0);
																																																																																																								if(n == 0)
																																																																																																													break;
																																																																																																																	fwrite(buf, 1, 1, fp);
																																																																																																																				}
																																																																																																																							fclose(fp);
																																																																																																																										close(client_sockfd);
																																																																																																																												}
																																																																																																																													}
																																																																																																																														close(sock_fd);
																																																																																																																															return 0;
																																																																																																																															}
																																																																																																																															