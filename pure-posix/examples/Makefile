
PURE_FLAGS=-L ./posix -I ./posix

server: prep
	pure $(PURE_FLAGS) socket_server.pure
client: prep
	pure $(PURE_FLAGS) socket_client.pure
prep: cleanbuild
	if ! [ -f ../posix.so ] ; then cd ..;make;cd examples; fi
	test -d "./posix" || mkdir -p "./posix"
	test -f ../posix.so 
	cp ../posix.pure ../socket.pure ../posix.so ./posix
cleanbuild:
	rm -rf ./posix