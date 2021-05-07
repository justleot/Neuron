FROM ubuntu:latest
WORKDIR /natural

RUN apt-get -y update
RUN apt-get -y install build-essential
RUN apt-get -y install manpages-dev
RUN apt-get -y install gcc-10 g++-10
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 100 --slave /usr/bin/g++ g++ /usr/bin/g++-10 --slave /usr/bin/gcov gcov /usr/bin/gcov-10

COPY . /natural

RUN ["chmod", "+x", "/natural/shell.sh"]

CMD /natural/shell.sh
