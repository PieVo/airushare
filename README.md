Airushare
=========
This application is a clone of the original ushare for geexbox. Airushare adds the functionality to play music from a shairport pipe. With this function a lightweight apple airplay to upnp/dlna bridge can be easily made with just 2 tools.

How does it work
================
Shairport has the ability to send audio through a pipe. This data is picked up by airushare and can then be transmitted to upnp receivers.

The data from the shairport pipe is lpcm encoded and I found that many player cannot handle this format. This is the reasong that a wav header is placed in front of the data. To send the right amount of data and prevent under/overflows in shairport a timer makes sure the right amount of data is sent to the receiver.

How do I use it
===============
1. create an audio pipe
mkfifo /tmp/music/airplay.wav

2. start shairport
shairport -v -m tinysvcmdns -a AirplayBridge -o pipe -- /tmp/music/Airplay.wav &

3. unblock the pipe
cat /tmp/music/airplay.wav

4. start airushare
ushare -v -n AirplayBridge -c /tmp/music &

5. select "AirplayBridge" as airplay target on you're iphone

6. select airplay.wav on your upnp/dlna media player


