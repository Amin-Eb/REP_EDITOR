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
    pane.send_keys("ls", enter=True)
    s = '\n'.join(pane.cmd('capture-pane', '-p').stdout)
    if s != the_cont:
    	flag = False
    session.kill()
    pass
   
@then('we see the output')
def step_impl(context):
    assert flag is True
