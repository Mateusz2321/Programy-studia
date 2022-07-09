

class ActionNameMapper():

    def get_user_friendly_action_name(self,string:str):
        return string.replace("_"," ")

    def get_normal_action_name(self,string:str):
        return string.replace(" ", "_")