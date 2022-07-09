import testlink
import subprocess
import datetime

cmd = ['pytest','test.py']
output = str(subprocess.Popen(cmd, stdout = subprocess.PIPE).communicate()[0])
if "passed" in output:
    result = 'p'
else:
    result = 'f'
# print(result)

TESTLINK_API_PYTHON_SERVER_URL = 'http://192.168.56.101/lib/api/xmlrpc/v1/xmlrpc.php'
TESTLINK_API_PYTHON_DEVKEY = 'd0c240d6683e53f58a35781ee0978c2b'
tlh = testlink.TestLinkHelper(TESTLINK_API_PYTHON_SERVER_URL,TESTLINK_API_PYTHON_DEVKEY)
tls = testlink.TestlinkAPIClient(tlh._server_url,tlh._devkey,verbose = False)
# tls.listProjects()
# print(tls.getProjectTestPlans(1))
# print(tls.countTestPlans())
# print(tls.countTestSuites())
# print(tls.countTestCasesTP())
# print(tls.getTestCaseIDByName('Test automatyczny'))

newResult = tls.reportTCResult(testplanid=2, status = 'p',
                buildid=1, testcaseexternalid='P01-2', notes="logging test",
                               timestamp=datetime.datetime.now().strftime("%Y-%m-%d %H:%M"))
