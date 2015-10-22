# encoding=utf-8
import sys
import yaml
import pexpect
import getpass
import socket
import node_list_pb2

yamlFileName = 'node_list.yaml'

#存放yaml文件解析的配置文件
initFileDict = {}

def sshCmd(user, ip, cmd, passwd):
	ret = -1
	ssh = pexpect.spawn('ssh %s@%s "%s"' % (user, ip, cmd))
	try:
		i = ssh.expect(['password:', 'continue connecting (yes/no)?'], timeout = 5)
	
		if 1 == i:
			ssh.sendline('yes\n')
			ssh.expect('password:')
	
		ssh.sendline(passwd)
		ssh.sendline(cmd)
		r = ssh.read()
		print r
		ret = 0
	
	except pexpect.EOF:
		print 'get an EOF'
		ssh.close()
		ret = -1
	
	except pexpect.TIMEOUT:
		print 'ssh TIMEOUT'
		ssh.close()
		ret = -2

	return ret


def scpFile(localFileList, user, ip, remoteDir, passwd):
	ret = -1
	scpStr = 'scp -rp '
	for fileName in localFileList:
		scpStr = scpStr + fileName + ' '
	scp = pexpect.spawn(scpStr +  '%s@%s:%s' % (user, ip, remoteDir))
	try:
		i = scp.expect(['password:', 'continue connecting (yes/no)?'], timeout = 5)

		if 1 == i:
			scp.sendline('yes\n')
			scp.expect('password:')
	
		scp.sendline(passwd)
		r = scp.read()
		print r
		ret = 0
	
	except pexpect.EOF:
		print 'get an EOF'
		scp.close()
		ret = -1
	
	except pexpect.TIMEOUT:
		print 'scp TIMEOUT'
		scp.close()
		ret = -2

	return ret

if __name__ == '__main__':
	if len(sys.argv) > 1:
		yamlFileName = sys.argv[1]

	try:
		initFile = open(yamlFileName)
		initFileDict = yaml.load(initFile)
	except IOError as e:
		print "I/O error({0}): {1}".format(e.errno, e.strerror)
	except yaml.YAMLError, exc:
		print "Error in config file:", exc	

	print initFileDict

	for node in initFileDict['NodeList']:
		scpFile(initFileDict['SendFileList'][node['TYPE']], node['USER'], node['IP'],
			initFileDict['ToDir'], node['PASSWD'])
		for cmdLine in initFileDict['CMD'][node['TYPE']]:
			sshCmd(node['USER'], node['IP'], cmdLine, node['PASSWD'])
