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
    print(tmp[0])
  #  tmp[0] = ''
  #  tmp[len(tmp)-1] = ''
    s = ""
    for i in range(0, len(tmp) ):
    	s = s + tmp[i] + '\n'

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
