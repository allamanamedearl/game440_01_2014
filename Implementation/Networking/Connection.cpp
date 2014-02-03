#include "Connection.h"

using namespace ManaCraft::Networking;

Connection::Connection(char* host, Uint16 port) {
	// Resolve the host and port provided
	if (SDLNet_ResolveHost(&mIPAddress, host, port) < 0) {
		printf("Unable to resolve host: %s\n", SDLNet_GetError());
		exit(1); // Should be changed
	}

	// Connections begin CLOSED.
	mStatus = DISCONNECTED;
}

Connection::Connection(TCPsocket sock) {
	// This constructor is primarily used as the way of returning accepted sockets
	// as a Connection object
	mSocket = sock;
	
	// Get the address information of the socket
	mRemoteIP = SDLNet_TCP_GetPeerAddress(mSocket);
}

NETWORKING_API int Connection::Open() {
	// Try to open a socket with IP data stored in mIPAddress
	mSocket = SDLNet_TCP_Open(&mIPAddress);

	// On success, change status to CONNECTED and return true
	if (mSocket) {
		mStatus = CONNECTED;
		return 1;
	}

	// If all else fails, return false
	return 0;
}

NETWORKING_API int Connection::Close() {
	// Simply close the socket and set the connection status to DISCONNECTED.
	SDLNet_TCP_Close(mSocket);
	mStatus = DISCONNECTED;

	return 0;
}

NETWORKING_API Connection* Connection::Listen() {
	// Connection must be OPEN and set as a SERVER (host == NULL)
	if (mSocket && mIPAddress.host == NULL) {
		// Listen for a connection and grab it
		TCPsocket sock = SDLNet_TCP_Accept(mSocket);

		// When we have a socket, wrap it in a Connection and return it.
		if (sock) {
			return new Connection(sock);
		}
	}

	// If all else fails, return NULL
	return NULL;
}

NETWORKING_API int Connection::ReceiveData(byte* buf) {
	// Recieve some data.
	// Coming soon to a repo near you.
	return 0;
}

NETWORKING_API int Connection::SendData(byte* payload) {
	// Send data over mSocket.
	// Coming soon to a repo near you.
	return 0;
}

NETWORKING_API int Connection::SendData(Packet& payload) {
	// Send data over mSocket
	// Coming soon to a repo near you.
	return 0;
}

NETWORKING_API std::string Connection::GetUsername() const {
	return mUsername;
}

NETWORKING_API IPaddress Connection::GetIP() const {
	// If we have created a connection via an incoming socket,
	// return the remoteIP info instead of the local IP.
	if (mIPAddress.port == NULL) {
		return *mRemoteIP;
	}

	// Otherwise return the local IP information.
	return mIPAddress;
}

NETWORKING_API TCPsocket Connection::GetSocket() const {
	return mSocket;
}

NETWORKING_API ConnectionStatus Connection::GetStatus() const {
	return mStatus;
}