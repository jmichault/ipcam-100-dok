#!/usr/bin/env sh
################################################################
# skripto por aŭtomate traduki frazon
################################################################

src="$1"
dst="$2"
txt="$3"
#echo "appel traduko pour :$txt." >>traduko.trc

cook=`find _traduko.jar -mmin -15 2>/dev/null`

PROVO=0
MAXPROVO=4


while [ $PROVO -le $MAXPROVO ]
do

if [ x$cook = x ]
then
  curl -c _traduko.jar -A 'Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0' \
   "https://translate.google.com" -o /dev/null 2>/dev/null
fi


MSG=$(curl -b _traduko.jar -A 'Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0' \
 --refer "https://translate.google.com/" \
 "https://translate.google.com/translate_a/single?client=webapp&sl=${src}&tl=${dst}&hl=${dst}&dt=at&dt=bd&dt=ex&dt=ld&dt=md&dt=qca&dt=rw&dt=rm&dt=ss&dt=t&dt=gt&pc=1&otf=1&ssel=0&tsel=0&kc=1&tk=&ie=UTF-8&oe=UTF-8" \
--data-urlencode "q=${txt}" 2>/dev/null \
  |sed "s/\\\\u003d/=/g;s/\\\\u003c/</g;s/\\\\u003e/>/g" \
  |sed "s/\\\\u200b/\xe2\x80\x8b/g" \
  |grep "\",null,null,[0-9]"|head -n 1|sed "s/\",\".*//;s/^[,\[]*\"//" \
  | tr -d "\n" \
  | sed "s/\\\ [nN]/n/g;s/] (/](/g;s/ __ / __/g" \
  | sed "s/\. \\\n$/.  \\\n/" \
)
#echo "résulta traduko :$MSG." >>traduko.trc

  if [ "x$MSG" = "x" ]
  then
    cook=""
    sleep 1
  else
    echo -n "$MSG"
    break;
  fi
  PROVO=$(($PROVO+1))
done
if [ "x$MSG" = "x" ]
then
   echo -n "$txt"
fi 
