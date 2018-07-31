FROM ubuntu:16.04
MAINTAINER slashxp@naver.com
COPY server /code/
COPY ser3 /code/
WORKDIR /code
EXPOSE 3001
RUN apt-get -y -qq update && \
		 apt-get -y -qq install gcc && \
		 apt-get -y -qq install netbase
CMD ./server a.c 12345
