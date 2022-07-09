from selenium import webdriver
from selenium.webdriver.common.by import By
import time

def test():
    driver = webdriver.Firefox(executable_path="C:\Selenium\geckodriver")
    driver.get("http://a.testaddressbook.com/")
    element = driver.find_element(By.ID,"sign-in")
    element.click()
    time.sleep(1)
    element = driver.find_element(By.ID,"session_email")
    element.send_keys("admin@admin.pl")
    time.sleep(1)
    element = driver.find_element(By.ID,"session_password")
    element.send_keys("admin")
    element = driver.find_element(By.NAME,"commit")
    element.submit()
    time.sleep(1)
    element = driver.find_element(By.CLASS_NAME,"alert-notice")
    result = element.get_attribute("innerHTML")

    time.sleep(1)
    driver.quit()

    assert result == "Bad email or password.","test passed"
