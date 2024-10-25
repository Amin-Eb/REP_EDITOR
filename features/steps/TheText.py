from behave import *
import libtmux


@given('test.txt')
def step_impl(context):
    the_file = open("steps/test.txt", "r")
    global the_cont 
    the_cont = the_file.readlines()
    the_file.close()
    pass

@when('we run REP')
def step_impl(context):
    global flag
    flag = True
    server = libtmux.Server()
    session = server.new_session(session_name="tester")
    window = session.new_window()
    pane = window.panes[0]
    pane.send_keys("./steps/REP steps/test.txt", enter=True)
    tmp = pane.cmd('capture-pane', '-p').stdout
    print(the_cont)
    for i in range(0, 24):
    	tmp[i] = tmp[i][4:]
    for i in range(0, 24):
    	if tmp[i]+'\n' != the_cont[i]:
    	    flag = False
    session.kill()
    pass
   
@then('we see the output')
def step_impl(context):
    assert flag == True
