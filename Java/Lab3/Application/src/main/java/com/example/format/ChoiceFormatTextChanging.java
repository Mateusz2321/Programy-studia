package com.example.format;

import java.text.ChoiceFormat;


public class ChoiceFormatTextChanging {

    public String getPolishContinentAreasFormat(String number){

        Integer x=Integer.parseInt(number);
        String number2;
        ChoiceFormat fmt;
        if(x>100){
            x=x%100;
            number2=x.toString();
            fmt = new ChoiceFormat(
                    "0#obszarów miejskich|1#obszarów miejskich|2#obszary miejskie|2<obszary miejskie|5#obszarów miejskich|5<obszarów miejskich|22#obszary miejskie" +
                            "|22<obszary miejskie|25#obszarów miejskich|25<obszarów miejskich|32#obszary miejskie|32<obszary miejskie|35#obszarów miejskich" +
                            "|35<obszarów miejskich" +
                            "|42#obszary miejskie|42<obszary miejskie|45#obszarów miejskich|45<obszarów miejskich|52#obszary miejskie|52<obszary miejskie|55#obszarów miejskich" +
                            "|55<obszarów miejskich|62#obszary miejskie" +
                            "|62<obszary miejskie|65#obszarów miejskich|65<obszarów miejskich" +
                            "|72#obszary miejskie|72<obszary miejskie|75#obszarów miejskich|75<obszarów miejskich|82#obszary miejskie|82<obszary miejskie" +
                            "|85#obszarów miejskich|85<obszarów miejskich|92#obszary miejskie|92<obszary miejskie|95#obszarów miejskich|95<obszarów miejskich");
        }

        else{
            fmt = new ChoiceFormat(
                    "0#obszarów miejskich|1#obszar miejski|2#obszary miejskie|2<obszary miejskie|5#obszarów miejskich|5<obszarów miejskich|22#obszary miejskie" +
                            "|22<obszary miejskie|25#obszarów miejskich|25<obszarów miejskich|32#obszary miejskie|32<obszary miejskie|35#obszarów miejskich" +
                            "|35<obszarów miejskich" +
                            "|42#obszary miejskie|42<obszary miejskie|45#obszarów miejskich|45<obszarów miejskich|52#obszary miejskie|52<obszary miejskie|55#obszarów miejskich" +
                            "|55<obszarów miejskich|62#obszary miejskie" +
                            "|62<obszary miejskie|65#obszarów miejskich|65<obszarów miejskich" +
                            "|72#obszary miejskie|72<obszary miejskie|75#obszarów miejskich|75<obszarów miejskich|82#obszary miejskie|82<obszary miejskie" +
                            "|85#obszarów miejskich|85<obszarów miejskich|92#obszary miejskie|92<obszary miejskie|95#obszarów miejskich|95<obszarów miejskich");
            number2=number;
        }

        String result=""+number+" "+fmt.format(Integer.parseInt(number2));
        return result;
    }
    public String getPolishContinentCountriesFormat(String number){

        Integer x=Integer.parseInt(number);
        String number2;
        ChoiceFormat fmt;
        if(x>100){
            x=x%100;
            number2=x.toString();
            fmt = new ChoiceFormat(
                    "0#państw|1#państw|2#państwa|2<państwa|5#państw|5<państw|22#państwa|22<państwa|25#państw|25<państw|32#państwa|32<państwa|35#państw|35<państw" +
                            "|42#państwa|42<państwa|45#państw|45<państw|52#państwa|52<państwa|55#państw|55<państw|62#państwa|62<państwa|65#państw|65<państw" +
                            "|72#państwa|72<państwa|75#państw|75<państw|82#państwa|82<państwa|85#państw|85<państw|92#państwa|92<państwa|95#państw|95<państw");
        }

        else{
            fmt = new ChoiceFormat(
                    "0#państw|1#państwo|2#państwa|2<państwa|5#państw|5<państw|22#państwa|22<państwa|25#państw|25<państw|32#państwa|32<państwa|35#państw|35<państw" +
                            "|42#państwa|42<państwa|45#państw|45<państw|52#państwa|52<państwa|55#państw|55<państw|62#państwa|62<państwa|65#państw|65<państw" +
                            "|72#państwa|72<państwa|75#państw|75<państw|82#państwa|82<państwa|85#państw|85<państw|92#państwa|92<państwa|95#państw|95<państw");
            number2=number;
        }

        String result=""+number+" "+fmt.format(Integer.parseInt(number2));
        return result;
    }
    public String getEnglishCitiesFormat(String number){
        String result=new String("");
        ChoiceFormat fmt = new ChoiceFormat(
                "0#are|1#is|2#are|2<are");
        result=fmt.format(Integer.parseInt(number));
        fmt = new ChoiceFormat(
                "0#cities|1#city|2#cities|2<cities");
        result=result+" "+number+" "+fmt.format(Integer.parseInt(number));

        return result;
    }
    public String getEnglishContinentAreasFormat(String number){
        String result=new String("");
        ChoiceFormat fmt = new ChoiceFormat(
                "0#urban areas| 1#urban area|2#urban areas|2<urban areas");
        result=""+number+" "+fmt.format(Integer.parseInt(number));
        return result;
    }
    public String getEnglishContinentCountriesFormat(String number){
        String result=new String("");
        ChoiceFormat fmt = new ChoiceFormat(
                "0#countries|1#country|2#countries|2<countries");
        result=""+number+" "+fmt.format(Integer.parseInt(number));
        return result;
    }
    public String getCitiesFormat(String number){

        Integer x=Integer.parseInt(number);
        String number2;
        ChoiceFormat fmt;
        if(x>100){
            x=x%100;
            number2=x.toString();
            fmt = new ChoiceFormat(
                    "0#miast| 1#miast|2#miasta|2<miasta|5#miast|5<miast|22#miasta|22<miasta|25#miast|25<miast|32#miasta|32<miasta|35#miast|35<miast" +
                            "|42#miasta|42<miasta|45#miast|45<miast|52#miasta|52<miasta|55#miast|55<miast|62#miasta|62<miasta|65#miast|65<miast" +
                            "|72#miasta|72<miasta|75#miast|75<miast|82#miasta|82<miasta|85#miast|85<miast|92#miasta|92<miasta|95#miast|95<miast");
        }

        else{
            fmt = new ChoiceFormat(
                    "0#miast| 1#miasto|2#miasta|2<miasta|5#miast|5<miast|22#miasta|22<miasta|25#miast|25<miast|32#miasta|32<miasta|35#miast|35<miast" +
                            "|42#miasta|42<miasta|45#miast|45<miast|52#miasta|52<miasta|55#miast|55<miast|62#miasta|62<miasta|65#miast|65<miast" +
                            "|72#miasta|72<miasta|75#miast|75<miast|82#miasta|82<miasta|85#miast|85<miast|92#miasta|92<miasta|95#miast|95<miast");
            number2=number;
        }

        String result=""+number+" "+fmt.format(Integer.parseInt(number2));
        return result;
    }
}
