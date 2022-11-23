# KV-RAT-CPP
## What is this?
This is a complete overhaul of the KV-RAT program **completely** in C++

### If its completely in C++, why are there python files?
I do not fully know C++ and how to do certain things, so as temporary fixes, I have python implementations until I figure out how to do it in C++

### Why?
I started to remake the client within C++ and ran into issues with handling data between the server that is in python to the client which is now in C++. So I decided to recreate both the server and the client using the SFML Library for networking.
I also decided this was best since now I don't have to swap back and forth with languages and can keep it relatively simple to read and understand.

And as usual a disclaimer
## Disclaimer
Before I continue, **This was made for educational purposes and I am not liable for what you use this software for and what happens.  I am not responsible for any thing people use this for. I made it to learn and I intend to never use it for bad intentions**

## How to use
- To build the project, download the source code in its entirety and then build which ever solution is needed, if needed, you may need to get/update some of the packages though nuget.
- If you don't want to build the project yourself, there should be a somewhat up to date version in the releases tab
## What's to come?
### Networking overhaul
SFML is just not worth it to continue using as a networking library for this project. Can be used for GUI based things though.
Potential libraries are as such

- Boost.Asio
- Winsock
- [C++ Networking library](https://cpp-netlib.org/index.html)
- [Libuv](https://github.com/libuv/libuv)

I may also switch from TCP to UDP depending on how screen capture ends up working

### Data handling
Because of how the screen capture function works, we have to serialize the output to be able to send it over the network for the server to receive and display. Not sure how I will handle this, but it will probably will have to be custom.

### P2P idea
Considering the server is just really another person, this would be considered peer to peer, so my new idea is as such.
Instead of having a seperate client and server application, it would only be one application and use arguments to change modes

server ex. `kv-rat.exe -server ip=127.0.0.1 -port=4560 -logging=false` || This allows the program to start as a server and receive data from a client

client ex. `kv-rat.exe -client -ip=127.0.0.1 -port=4560`  || This allows the program to start as a client and connect to the defined network details

### Why do all this
Well, with all the issues I have been having with this project and the libraries, I have decided that it would be easier and worth it in the long run to just make everything to fit the project
## Is this meant to be malicious?
The straight answer is **no**. I do not condone this software being used to exploit other people for either the benefit of the attacker or for blackmail. This was made for a friend of mine who finds humor in being messed with and I intend to keep it that way. It should never be hidden from the client that the software is running on their computer. This can also be noted from the KV in the name, which stands for *"Kasean Virus"* which also used to be known as *"The dumbasses virus"* as that is a running joke with this person.



