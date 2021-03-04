{
  if ( CONTMSG==1 && substr($1,1,1) != "\"")
  { # fino de plurlinia mesaĝo
    CONTMSG=0;
  }
  if ($1 == "msgid")
  {
    MSGID=substr($0,7);
    MSGSTR=substr($0,8,length($0)-8);
    MSGWRAP=0;
    if(MSGID=="\"\"")
    {
      CONTMSG=1;
      MSGWRAP=1;
    }
  }
  else if ( CONTMSG==1 && substr($1,1,1) == "\"")
  { # daŭrigo de plurlinia mesaĝo
    # enmemorigi MSGID-liniojn
    MSGID=MSGID "\n" $0;
    # enmemorigi netradukitan mesaĝon
    MSGSTR=MSGSTR substr($0,2,length($0)-2);
  }
  else if ($1 == "msgstr")
  {
    print "msgid " substr($0,7);
      $0="";
      getline
      while ( substr($1,1,1) == "\"")
      { # plurlinia mesaĝo
        print $0;
	next;
        $0="";
        getline
      }
    print "msgstr \"\"";
    print $0;
  }
  else
  {
    print $0;
  }
}
