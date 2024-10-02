from behave import *
import libtmux

flag = True

@given('test.txt')
def step_impl(context):
    the_file = open("steps/test.txt", "r")
    global the_cont 
    the_cont = the_file.read()
    the_file.close()
    pass

@when('we run REP')
def step_impl(context):
    server = libtmux.Server()
    session = server.new_session(session_name="tester")
    window = session.new_window()
    pane = window.panes[0]
    pane.send_keys("./steps/REP steps/test.txt", enter=True)
    tmp = pane.cmd('capture-pane', '-p').stdout
    tmp[0] = ''
    tmp[len(tmp)-1] = ''
    s = ""
    for i in range(1, len(tmp) - 2):
    	s = s + tmp[i] + '\n'
    s = s + tmp[len(tmp) - 2]
    if s != the_cont:
    	flag = False
    print(">>>")
    print(s)
    print("<<<")
    print(the_cont)
    print(">>>", (s == the_cont))
    print(len(s))
    print(len(the_cont))
    session.kill()
    pass
   
@then('we see the output')
def step_impl(context):
    assert flag is False
