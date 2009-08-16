#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/* Copyright (c) 2009 by Mike Maul <mike.maul@gmail.com>.

   This file is an extension to the Pure programming language and system.

   Pure is free software: you can redistribute it and/or modify it under the
   terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

   Pure is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
   details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>. */


/* Wrappers for c library functions. */

void * pure_sockaddr (int family, char *address_str, int port) {
  struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in)); 
  if (strcmp(address_str,"*") == 0) {
    address->sin_addr.s_addr=INADDR_ANY;
  } else {
    address->sin_addr.s_addr=inet_addr( address_str );
  }
  address->sin_port = htons(port);
  address->sin_family = family;
  int nAddressSize=sizeof(struct sockaddr_in);
  return address;
}

int pure_bind (int sockfd, void *address_ptr) {
  struct sockaddr_in *address=address_ptr;
  return bind(sockfd,(struct sockaddr *)address,sizeof(struct sockaddr_in));
}

int pure_accept( int socket, void * address) {
  int *i = malloc(sizeof(int));
  *i=sizeof(struct sockaddr);
  return accept(socket,(struct sockaddr *)address,i);
}

int pure_connect (int sockfd, void *address_ptr) {
  struct sockaddr_in *address=address_ptr;
  return connect(sockfd,(struct sockaddr *)address,sizeof(struct sockaddr_in));
}

int pure_write_string(int fd, char *buf) {
  return write(fd,buf,strlen(buf));
}

char *pure_read_string(int fd,int len) {
  char * buf = (char *)malloc(sizeof(char)*len);
  int ret=read(fd,buf,len);
  if(ret == 0) {
    return "";
  } else if (ret < 0 ) {
    return NULL;
  } else {
    return buf;
  }
}



