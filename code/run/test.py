import docker

client = docker.from_env()
client.containers.run("ubu_cobot", ports={'3001/tcp': None}, detach=True, tty=True)
