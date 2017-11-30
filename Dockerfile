FROM 	ubuntu:14.04


RUN 	apt-get update \
	&& apt-get install -y \
		ksh bison flex gperf libasound2-dev libgl1-mesa-dev \
    		libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libjpeg-dev \
    		libpng-dev libx11-dev libxml2-dev libxslt1-dev libxt-dev \
    		libxxf86vm-dev pkg-config x11proto-core-dev \
    		x11proto-xf86vidmode-dev libavcodec-dev mercurial \
    		libgtk2.0-dev libgtk-3-dev \
    		libxtst-dev libudev-dev libavformat-dev

RUN	dpkg --add-architecture i386 \
	&& apt-get update \
	&& apt-get install -y \
    		gcc-multilib \
    		g++-multilib \
    		zlib1g-dev:i386

RUN     apt-get install -y wget unzip software-properties-common python-software-properties

RUN	add-apt-repository ppa:openjdk-r/ppa \
	&& apt-get update \
	&& apt-get install -y openjdk-8-jdk \
	&& update-alternatives --config java \
	&& update-alternatives --config javac

ENV 	JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64

RUN	wget https://services.gradle.org/distributions/gradle-1.8-bin.zip \
	&& mkdir /opt/gradle \
	&& unzip -d /opt/gradle gradle-1.8-bin.zip \
	&& export PATH=$PATH:/opt/gradle/gradle-1.8/bin

RUN	ln -s /opt/gradle/gradle-1.8/bin/gradle /usr/bin/gradle

ENV	OPENJFX_BUILD bf0eb93f04f1

RUN	curl -O http://hg.openjdk.java.net/openjfx/8u-dev/rt/archive/$OPENJFX_BUILD.tar.gz \
	&& tar zxf $OPENJFX_BUILD.tar.gz
 
WORKDIR rt-$OPENJFX_BUILD

RUN	mkdir tmp \
	&& cd tmp \
	&& chmod +x ../buildSrc/crosslibs/crosslibs-armv6hf.sh \
	&& ../buildSrc/crosslibs/crosslibs-armv6hf.sh \
	&& cd ..

RUN	sed -i 's/ARMV6HF\.compileSwing \= false;/ARMV6HF\.compileSwing \= true;/g' buildSrc/armv6hf.gradle

RUN	sed -i 's/ARMV6HF\.includeSwing \= false;/ARMV6HF\.includeSwing \= true;/g' buildSrc/armv6hf.gradle

RUN	sed -i 's/ARMV6HF\.compileMediaNative \= false;/ARMV6HF\.compileMediaNative \= true;/g' buildSrc/armv6hf.gradle

RUN	sed -i 's/ARMV6HF\.compileWebnodeNative \= false;/ARMV6HF\.compileWebnodeNative \= true;/g' buildSrc/armv6hf.gradle

RUN	sed -i 's/ARMV6HF\.disableMedia \= true;/ARMV6HF\.disableMedia \= false;/g' buildSrc/armv6hf.gradle

RUN	sed -i 's/"-DENABLE_GST_FFMPEG=1"/"-DENABLE_GST_FFMPEG=0"/g' buildSrc/armv6hf.gradle

#RUN	sed -i 's/ffdec_mp3/mad/g' modules/media/src/main/native/jfxmedia/platform/gstreamer/GstPipelineFactory.cpp
