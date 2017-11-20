# hono-binding
AGL binding to communicate with Eclipse hono instance via REST adapter

## Setup

 

```bash

git clone https://github.com/Vamsi3012/hono-binding.git

cd hono-service

```

 

## Build  for AGL

 

```bash

#If the SDK is already installed in the XDS server, then setup your build environement.

./xdt/sdk/environment-setup-corei7-64-agl-linux

 

#if not installed, install either the SDK directly (E.g. SDK version Daring Dab 4.0.2 for intel)

wget https://download.automotivelinux.org/AGL/release/dab/4.0.2/intel-corei7-64/deploy/sdk/poky-agl-glibc-x86_64-agl-demo-platform-crosssdk-corei7-64-toolchain-4.0.2.sh

cd Downloads

chmod +x poky-agl-glibc-x86_64-agl-demo-platform-crosssdk-corei7-64-toolchain-4.0.2.sh

./poky-agl-glibc-x86_64-agl-demo-platform-crosssdk-corei7-64-toolchain-4.0.2.sh

#When prompted, simply install the SDK in the default location.

./opt/poky-agl/4.0.2/environment-setup-corei7-64-agl-linux

cd ..

 

#build your application

cd root_dir_of_application

./conf.d/autobuild/agl/autobuild package

```

 

## Build for 'native' Linux distros (Fedora, openSUSE, Debian, Ubuntu, ...)

 

```bash
#The below command builds the widget file necessary for deploying
./conf.d/autobuild/linux/autobuild package

#The following command build the service which is just sufficient for testing the binding
./conf.d/autobuild/linux/autobuild build

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
 

### Native Linux

For native build you need to have tools **afb-daemon**.

You can build it by your self [app-framework-binder][app-framework-binder], or use binary package from OBS: [opensuse.org/LinuxAutomotive][opensuse.org/LinuxAutomotive]

 

```bash
#Start the binding
afb-daemon --port=1234  --binding=hono_root_directory/build/package/lib/hono.so --token=1

 

#On a client shell
afb-client-demo -H ws://localhost:1234/api?token=1

#For listing all available verbs:
hono list

#On execution, the output is as shown below. the binding can register a device, send event and telemetry data. However, this binding does not support the authentication of the devices. Thus this has to be done using the API given here https://www.eclipse.org/hono/component/device-registry/#using-the-credentials-api-via-http
ON-REPLY 1:hono/list: OK
{
  "response":[
    {
      "connect":"Connects a device to hono",
      "commnad":"hono connect",
      "Json Arguments":{
        "host_name":"172.18.0.110",
        "port":"28080",
        "tenant_name":"DEFAULT_TENANT"
      }
    },
    {
      "sendt":"Sends Telemetry data to hono",
      "command":"hono sendt",
      "Json Arguments":{
        "sensor_id":"sensor5",
        "host_name":"172.18.0.110",
        "port":"8080",
        "tenant_name":"DEFAULT_TENANT",
        "field":"engineSpeed",
        "value":45.450000
      }
    },
    {
      "sende":"Sends event data to hono",
      "command":"hono sende",
      "Json Arguments":{
        "sensor_id":"sensor5",
        "host_name":"172.18.0.110",
        "port":"8080",
        "tenant_name":"DEFAULT_TENANT",
        "field":"engineSpeed",
        "event":"event_name"
      }
    },
    {
      "list":"lists all the verbs and their information."
    }
  ],
  "jtype":"afb-reply",
  "request":{
    "status":"success",
    "info":"Verb that lists all available verbs",
    "uuid":"ae2f6528-e0ad-44d5-a324-067b27d7b202"
  }
}

 

```

 

 

And rebuild your application

 

[opensuse.org/LinuxAutomotive]:https://en.opensuse.org/LinuxAutomotive

[app-framework-binder]:https://gerrit.automotivelinux.org/gerrit/#/admin/projects/src/app-framework-binder
