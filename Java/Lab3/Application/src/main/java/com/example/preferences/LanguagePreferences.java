package com.example.preferences;

import java.util.prefs.Preferences;

public class LanguagePreferences {
    private Preferences preferences;
    public String getPreferences(String def){
        preferences=Preferences.userRoot().node(this.getClass().getName());
        String pref=preferences.get("Language", def);
        return pref;
    }
    public String getSystemPreferences(String def){
        preferences=Preferences.systemRoot().node(this.getClass().getName());
        String pref=preferences.get("Language", def);
        return pref;
    }

    public void setPreferences(String language){
        preferences=Preferences.userRoot().node(this.getClass().getName());
        preferences.put("Language",language);
    }
    public void setSystemPreferences(String language){
        preferences=Preferences.systemRoot().node(this.getClass().getName());
        preferences.put("Language",language);
    }
}
