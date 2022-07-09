import py
import pytest
from selenium import webdriver      #opakować w pytest lub inny framework, np. z assertami
from selenium.webdriver.common.by import By
import time
from selenium.webdriver.support.wait import WebDriverWait


def test1():
    actual_list=[]
    actual_length = 0
    with open("prices.txt","r") as pr:
        actual_list=pr.read().split("\n")
    actual_list.pop(-1)
    # create a new Firefox session
    driver = webdriver.Firefox(executable_path="C:\Selenium\mozilla geckodriver\geckodriver")
    driver.implicitly_wait(30)
    driver.maximize_window()

    # navigate to the application home page
    driver.get('http://automationpractice.com/index.php')
    search_cost= driver.find_elements(By.CLASS_NAME, "product-price")
    lst= []
    for i in search_cost:
        cost=i.get_attribute("innerHTML").replace("\t","").replace("\n","")[1:]
        lst.append(cost)
    the_same= True
    if len(actual_list) == 0:
        actual_list.clear()
        actual_length=0
        with open("prices.txt","w") as pr:
            for i in lst:
                pr.write(str(i)+"\n")
        print("Prices saved to file")
    else:
        if len(lst) != len(actual_list):
            print("Price test failed-length changed")
        else:
            for i in range(len(actual_list)):
                if actual_list[i] != lst[i]:
                    print("Price test failed")
                    the_same = False
                    break
            if the_same is True:
                print("Price test passed- prices didn' t change")


    time.sleep(4)
    driver.quit()
    time.sleep(2)
def test2():
    #Test2- przeklikanie
    driver = webdriver.Firefox(executable_path="C:\Selenium\mozilla geckodriver\geckodriver")
    driver.get("http://a.testaddressbook.com/")
    element = driver.find_element(By.ID,"sign-in")
    element.click()
    time.sleep(4)
    element = driver.find_element(By.ID,"session_email")
    element.send_keys("admin@admin.pl")
    time.sleep(1)
    element = driver.find_element(By.ID,"session_password")
    element.send_keys("admin")
    element = driver.find_element(By.NAME,"commit")
    element.submit()
    time.sleep(2)
    element = driver.find_element(By.CLASS_NAME,"alert-notice")
    result = element.get_attribute("innerHTML")
    assert result == "Bad email or password.","test passed"
    assert result != "Bad email or password.", "test failed"

    time.sleep(4)
    driver.quit()
    time.sleep(2)

