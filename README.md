# cobot

작동 과정
1. 서버의 cobot/settings 에서 docker build -t <ImageName> (Dockerfile로부터 도커 이미지 빌드)
2. 서버의 cobot/code/run 에서 python test.py (빌드한 도커 이미지로부터 컨테이너 생성 및 시작 -> 서버 소켓 생성 후 대기)
3. 클라이언트의 cobot/code/run 에서 ./clit hello2.c <ServerIP> 12345 23456

  - (1) 클라이언트 소켓 생성 후 서버에 연결

  - (2) 서버에 hello2.c 전송

  - (3) 서버에서 hello2.c 컴파일 후 실행

  - (4) 서버에서 hello2.c 의 실행 결과를 클라이언트로 전송

  - (5) 클라이언트에서 hello2.c 의 결과 출력
