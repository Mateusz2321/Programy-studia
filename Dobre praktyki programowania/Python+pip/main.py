from steering.question import Question


class Aplikacja():
    def __init__(self):
        self.question = Question()

    def start_queries(self):
        weather_now = self.question.get_actual_weather()
        print("----------------")
        print("Pogoda teraz:")
        print("Temperatura: "+str(weather_now.temperature))
        print("----------------")
        weather = self.question.get_search_weather_data()
        print("Pogoda w Londynie:")
        print("Temperatura: "+str(weather.temperature))
        print("Temperatura minimalna: " + str(weather.temperature_min))
        print("Temperatura maksymalna: " + str(weather.temperature_max))
        weather_future = self.question.get_future_weather()
        print("Pogoda w Londynie:")
        list= weather_future.temperature_list
        print("Temperatura w najbliższych dniach:")
        for i in range(len(list)):
            print(str(i) + ") " + str(round(list[i]-273,1)))














if __name__ == '__main__':
    a = Aplikacja()
    a.start_queries()
