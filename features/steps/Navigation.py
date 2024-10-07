from behave import *
import libtmux

@given('The file opened by REP')
def step_impl(context):
    the_file = open("steps/test.txt", "r")
    global the_cont 
    the_cont = the_file.readlines()
    the_file.close()
    pass

@when('We use keys to navigate cursor')
def step_impl(context):
    global flag
    flag = True
    server = libtmux.Server()
    session = server.new_session(session_name="tester")
    window = session.new_window()
    pane = window.panes[0]
    pane.send_keys("./steps/REP steps/test.txt", enter=True)

    #testing pag-down key
    pane.send_keys("PageDown", enter=False)
    tmp = pane.cmd('capture-pane', '-p').stdout
    for i in range(0,24):
        if tmp[i] != str(i + 25):
            flag = False

    #testing page-up key
    pane.send_keys("PageUp", enter=False)
    tmp = pane.cmd('capture-pane', '-p').stdout
    for i in range(0,24):
        if tmp[i] != str(i + 1):
            flag = False

    #testing End-page key
    pane.send_keys("End", enter=False)
    tmp = pane.cmd('capture-pane', '-p').stdout
    for i in range(0,24):
        if tmp[i] != str(i + 76):
            flag = False

    #testing Home-page key
    pane.send_keys("Home", enter=False)
    tmp = pane.cmd('capture-pane', '-p').stdout
    for i in range(0,24):
        if tmp[i] != str(i + 1):
            flag = False

    session.kill()
    pass

@then('the cursor moves')
def step_impl(context):
    assert flag == True
