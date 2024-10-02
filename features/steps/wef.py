from behave import *
import libtmux


def step_impl():
    the_file = open("test.txt", "r")
    global the_cont 
    the_cont = the_file.readlines()
    the_file.close()
    pass

def step_impl1():
    global flag
    flag = True
    server = libtmux.Server()
    session = server.new_session(session_name="tester")
    window = session.new_window()
    pane = window.panes[0]
    pane.send_keys("./REP test.txt", enter=True)
    tmp = pane.cmd('capture-pane', '-p').stdout
    tmp[0] = ''
    tmp[len(tmp)-1] = ''
    for i in range(0, len(tmp) - 1):
        if tmp[i]+'\n' != the_cont[i-1]:
      	    flag = False

    print(">>>")
    print(tmp)
    print(the_cont)
    print("<<<")

    session.kill()
    pass
    
   
def step_impl2():
    assert flag == True

step_impl()
step_impl1()
step_impl2()
