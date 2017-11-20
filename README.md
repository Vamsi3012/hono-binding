# hono-binding
AGL binding to communicate with Eclipse hono instance via REST adapter

## Setup

 

```bash

git clone

cd hono

```

 

## Build  for AGL

 

```bash

#If the SDK is already installed then setup your build environement

./xdt/sdk/environment-setup-corei7-64-agl-linux

 

#if not installed, install either the SDK directly (E.g. SDK version Daring Dab 4.0.2 for intel)

wget https://download.automotivelinux.org/AGL/release/dab/4.0.2/intel-corei7-64/deploy/sdk/poky-agl-glibc-x86_64-agl-demo-platform-crosssdk-corei7-64-toolchain-4.0.2.sh

cd Downloads

chmod +x poky-agl-glibc-x86_64-agl-demo-platform-crosssdk-corei7-64-toolchain-4.0.2.sh

./poky-agl-glibc-x86_64-agl-demo-platform-crosssdk-corei7-64-toolchain-4.0.2.sh

#When prompted, simply install in the default location.

./opt/poky-agl/4.0.2/environment-setup-corei7-64-agl-linux

cd ..

 

#build your application

cd root_dir_of_application

./conf.d/autobuild/agl/autobuild package

```

 

## Build for 'native' Linux distros (Fedora, openSUSE, Debian, Ubuntu, ...)

 

```bash

./conf.d/autobuild/linux/autobuild package

```

 

 

## Deploy

 

### AGL

 

```bash

export YOUR_BOARD_IP=192.168.1.X

export APP_NAME=hono

scp build/${APP_NAME}.wgt root@${YOUR_BOARD_IP}:/tmp

ssh root@${YOUR_BOARD_IP} afm-util install /tmp/${APP_NAME}.wgt

APP_VERSION=$(ssh root@${YOUR_BOARD_IP} afm-util list | grep ${APP_NAME}@ | cut -d"\"" -f4| cut -d"@" -f2)

ssh root@${YOUR_BOARD_IP} afm-util start ${APP_NAME}@${APP_VERSION}

```

 

## TEST

 

### AGL

 

```bash

export YOUR_BOARD_IP=192.168.1.X

export PORT=8000

ssh root@${YOUR_BOARD_IP} afb-daemon --ws-client=unix:/run/user/0/apis/ws/helloworld --port=${PORT} --token='x' -v

 

#On an other terminal

ssh root@${YOUR_BOARD_IP} afb-client-demo -H 127.0.0.1:${PORT}/api?token=x helloworld ping true

#or

curl http://${YOUR_BOARD_IP}:${PORT}/api/helloworld/ping?token=x

#For a nice display

curl http://${YOUR_BOARD_IP}:${PORT}/api/helloworld/ping?token=x 2>/dev/null | python -m json.tool

```

 

### Native Linux

 

For native build you need to have tools **afb-daemon**.

You can build it by your self [app-framework-binder][app-framework-binder], or use binary package from OBS: [opensuse.org/LinuxAutomotive][opensuse.org/LinuxAutomotive]

 

```bash

afb-daemon --port=1234  --binding=hono_root_directory/build/package/lib/hono.so --token=1

 

#On a client shell

afb-client-demo -H ws://localhost:1234/api?token=1

#For listing all available verbs:

hono list

 

```

 

 

And rebuild your application

 

[opensuse.org/LinuxAutomotive]:https://en.opensuse.org/LinuxAutomotive

[app-framework-binder]:https://gerrit.automotivelinux.org/gerrit/#/admin/projects/src/app-framework-binder
