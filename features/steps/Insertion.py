from behave import *
import libtmux

@given('opened test.txt')
def step_impl(context):
    the_file = open("steps/test.txt", "r")
    global the_cont 
    the_cont = the_file.readlines()
    the_file.close()
    pass

@when('we insert words, numbers and ENTERs')
def step_impl(context):
    server = libtmux.Server()
    session = server.new_session(session_name="tester")
    window = session.new_window()
    pane = window.panes[0]
    pane.send_keys("./steps/REP steps/test.txt", enter=True)
    pane.send_keys("i", enter = False)
    for i in range(0,12):
    	pane.send_keys("s", enter = True)
    pane.send_keys("s", enter = False)
    global tmp
    tmp = pane.cmd('capture-pane', '-p').stdout
    pane.send_keys("S-Home", enter = False)
    session.kill()
    pass
   
@then('the changes will be applied to test.txt')
def step_impl(context):
    flag = True
    the_file = open("steps/test.txt", "r")
    the_cont = the_file.readlines()
    #for i in range (0,13):
    #	tmp[i] = str(tmp[i][4:])
    print(the_cont)
    print(tmp)
    for i in range (0,13):
        if the_cont[i] != tmp[i] + '\n':
            flag = False
            
    the_file.close()
    assert flag == True
