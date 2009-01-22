/*
Child, Internet Relay Chat Services
Copyright (C) 2005-2009  David Lebrun (target0@geeknode.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <child.h>
#include <globals.h>

void bot_god (Nick *, User *, Chan *, Wchan *);
void bot_owner (Nick *, User *, Chan *, Wchan *);
void bot_deowner (Nick *, User *, Chan *, Wchan *);
void bot_protect (Nick *, User *, Chan *, Wchan *, char *);
void bot_deprotect (Nick *, User *, Chan *, Wchan *, char *);
void bot_op (Nick *, User *, Chan *, Wchan *, char *);
void bot_deop (Nick *, User *, Chan *, Wchan *, char *);
void bot_halfop (Nick *, User *, Chan *, Wchan *, char *);
void bot_dehalfop (Nick *, User *, Chan *, Wchan *, char *);
void bot_voice (Nick *, User *, Chan *, Wchan *, char *);
void bot_devoice (Nick *, User *, Chan *, Wchan *, char *);
void bot_opall (Nick *, User *, Chan *, Wchan *);
void bot_deopall (Nick *, User *, Chan *, Wchan *);
void bot_halfopall (Nick *, User *, Chan *, Wchan *);
void bot_dehalfopall (Nick *, User *, Chan *, Wchan *);
void bot_voiceall (Nick *, User *, Chan *, Wchan *);
void bot_devoiceall (Nick *, User *, Chan *, Wchan *);
void bot_opopop (Nick *, User *, Chan *, Wchan *);
void bot_kick (Nick *, User *, Chan *, Wchan *, char *);
void bot_rkick (Nick *, User *, Chan *, Wchan *, char *);
void bot_kb (Nick *, User *, Chan *, Wchan *, char *);
void bot_rkb (Nick *, User *, Chan *, Wchan *, char *);
void bot_unban (Nick *, User *, Chan *, Wchan *, char *);
void bot_ban (Nick *, User *, Chan *, Wchan *, char *);
void bot_topic (Nick *, User *, Chan *, Wchan *, char *);
void bot_moo (Nick *, User *, Chan *, Wchan *, char *);
void bot_seen (Nick *, User *, Chan *, Wchan *, char *);
void bot_admin (Nick *, User *, Chan *, Wchan *);
void bot_fuckall (Nick *, User *, Chan *, Wchan *);
void bot_tb (Nick *, User *, Chan *, Wchan *, char *);

void child_init()
{
    addBotCommand("!voiceall",bot_voiceall,1);
    addBotCommand("!voice",bot_voice,1);
    addBotCommand("!unban",bot_unban,1);
    addBotCommand("!topic",bot_topic,1);
    addBotCommand("!tb", bot_tb,1);
    addBotCommand("!seen",bot_seen,0);
    addBotCommand("!protect",bot_protect,1);
    addBotCommand("!owner",bot_owner,1);
    addBotCommand("!opopop",bot_opopop,1);
    addBotCommand("!opall",bot_opall,1);
    addBotCommand("!op",bot_op,1);
    addBotCommand("!moo",bot_moo,1);
    addBotCommand("!kick",bot_kick,1);
    addBotCommand("!rkick",bot_rkick,1);
    addBotCommand("!kb",bot_kb,1);
    addBotCommand("!rkb",bot_rkb,1);
    addBotCommand("!halfopall",bot_halfopall,1);
    addBotCommand("!halfop",bot_halfop,1);
    addBotCommand("!god",bot_god,1);
    addBotCommand("!fuckall",bot_fuckall,1);
    addBotCommand("!devoiceall",bot_devoiceall,1);
    addBotCommand("!devoice",bot_devoice,1);
    addBotCommand("!deprotect",bot_deprotect,1);
    addBotCommand("!deowner",bot_deowner,1);
    addBotCommand("!deopall",bot_deopall,1);
    addBotCommand("!deop",bot_deop,1);
    addBotCommand("!dehalfopall",bot_dehalfopall,1);
    addBotCommand("!dehalfop",bot_dehalfop,1);
    addBotCommand("!ban",bot_ban,1);
    addBotCommand("!admin",bot_admin,0);
}

void child_cleanup()
{
    delBotCommand("!god");
    delBotCommand("!owner");
    delBotCommand("!deowner");
    delBotCommand("!protect");
    delBotCommand("!deprotect");
    delBotCommand("!op");
    delBotCommand("!deop");
    delBotCommand("!halfop");
    delBotCommand("!dehalfop");
    delBotCommand("!voice");
    delBotCommand("!devoice");
    delBotCommand("!opall");
    delBotCommand("!deopall");
    delBotCommand("!halfopall");
    delBotCommand("!dehalfopall");
    delBotCommand("!voiceall");
    delBotCommand("!devoiceall");
    delBotCommand("!opopop");
    delBotCommand("!kick");
    delBotCommand("!rkick");
    delBotCommand("!kb");
    delBotCommand("!rkb");
    delBotCommand("!unban");
    delBotCommand("!ban");
    delBotCommand("!topic");
    delBotCommand("!moo");
    delBotCommand("!seen");
    delBotCommand("!admin");
    delBotCommand("!fuckall");
    delBotCommand("!tb");
}

void bot_god (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan)
{
    Cflag *cflag;
    if (!IsAuthed(uptr)) return;

    cflag = find_cflag(uptr->nick,wchan->chname);
    if (!cflag && !IsFounder(uptr,chptr)) return;
    FakeMsg(whatbot(wchan->chname),wchan->chname,"stfu %s",nptr->nick);
}

void bot_owner (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan)
{
    if (!IsAuthed(uptr)) return;

    if (!IsFounder(uptr,chptr)) return;
    if (!IsOwner(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_OWNER,1,whatbot(wchan->chname));
}

void bot_deowner (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan)
{
    if (!IsAuthed(uptr)) return;

    if (!IsFounder(uptr,chptr)) return;
    if (IsOwner(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_OWNER,0,whatbot(wchan->chname));
}

void bot_protect (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2;

    if (!IsAuthed(uptr)) return;

    if (GetFlag(uptr,chptr) < me.chlev_admin && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') {
        if (!IsProtect(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_PROTECT,1,whatbot(wchan->chname));
    } else {
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (!IsFounder(uptr,chptr)) return;
        if (!IsProtect(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_PROTECT,1,whatbot(wchan->chname));
    }
}

void bot_deprotect (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2;
    
    if (!IsAuthed(uptr)) return;

    if (GetFlag(uptr,chptr) < me.chlev_admin && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') {
        if (IsProtect(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_PROTECT,0,whatbot(wchan->chname));
    } else {
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (!IsFounder(uptr,chptr)) return;
        if (IsProtect(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_PROTECT,0,whatbot(wchan->chname));
    }
}

void bot_op (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2;

    if (!IsAuthed(uptr)) return;

    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') { 
        if (!IsOp(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_OP,1,whatbot(wchan->chname));
    } else {
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (!IsOp(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_OP,1,whatbot(wchan->chname));
    }
}

void bot_deop (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2; 

    if (!IsAuthed(uptr)) return;

    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') { 
        if (IsOp(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_OP,0,whatbot(wchan->chname));
    } else {
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (IsOp(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_OP,0,whatbot(wchan->chname));
    }
}

void bot_halfop (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2; 
    
    if (!IsAuthed(uptr)) return;

    if (!arg2 || *arg2 == '\0') {
        if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
        if (!IsHalfop(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_HALFOP,1,whatbot(wchan->chname));
    } else {
        if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (!IsHalfop(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_HALFOP,1,whatbot(wchan->chname));
    }
}

void bot_dehalfop (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2; 
    
    if (!IsAuthed(uptr)) return;

    if (!arg2 || *arg2 == '\0') {
        if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
        if (IsHalfop(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_HALFOP,0,whatbot(wchan->chname));
    } else {
        if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (IsHalfop(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_HALFOP,0,whatbot(wchan->chname));
    }
}

void bot_voice (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all; 
    SeperateWord(arg2);
    Nick *nptr2; 
    
    if (!IsAuthed(uptr)) return;

    if (!arg2 || *arg2 == '\0') {
        if (GetFlag(uptr,chptr) < me.chlev_voice && !IsFounder(uptr,chptr)) return;
        if (!IsVoice(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_VOICE,1,whatbot(wchan->chname));
    } else {
        if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (!IsVoice(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_VOICE,1,whatbot(wchan->chname));
    }
}

void bot_devoice (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);
    Nick *nptr2;

    if (!IsAuthed(uptr)) return;

    if (!arg2 || *arg2 == '\0') {
        if (GetFlag(uptr,chptr) < me.chlev_voice && !IsFounder(uptr,chptr)) return;
        if (IsVoice(nptr->nick,wchan)) SetStatus(nptr,wchan->chname,CHFL_VOICE,0,whatbot(wchan->chname));
    } else {
        if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
        nptr2 = find_nick(arg2);
        if (!nptr2) return;
        if (IsVoice(nptr2->nick,wchan)) SetStatus(nptr2,wchan->chname,CHFL_VOICE,0,whatbot(wchan->chname));
    }
}

void bot_opall (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan)
{
    Member *member;
    Nick *nptr2;

    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;

    LIST_FOREACH(member_list, member, HASH(wchan->chname)) {
        if (!IsOp(member->nick,wchan) && !Strcmp(member->channel,wchan->chname)) {
            nptr2 = find_nick(member->nick);
            if (!nptr2) return;
            SetStatus(nptr2,chptr->channelname,CHFL_OP,1,whatbot(wchan->chname));
        }
    }
}

void bot_deopall (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan)
{
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;

    SendRaw("SVSMODE %s -o",wchan->chname);
}

void bot_halfopall (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan)
{
    Member *member;
    Nick *nptr2;
    
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;

    LIST_FOREACH(member_list, member, HASH(wchan->chname)) {
        if (!IsHalfop(member->nick,wchan) && !Strcmp(member->channel,wchan->chname)) {
            nptr2 = find_nick(member->nick);
            if (!nptr2) return;
            SetStatus(nptr2,chptr->channelname,CHFL_HALFOP,1,whatbot(wchan->chname));
        }
    }
}

void bot_dehalfopall (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan)
{
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;

    SendRaw("SVSMODE %s -h",wchan->chname);
}

void bot_voiceall (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan)
{
    Member *member;
    Nick *nptr2;
    
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
 
    LIST_FOREACH(member_list, member, HASH(wchan->chname)) {
        if (!IsVoice(member->nick,wchan) && !Strcmp(member->channel,wchan->chname)) {
            nptr2 = find_nick(member->nick);
            if (!nptr2) return;
            SetStatus(nptr2,chptr->channelname,CHFL_VOICE,1,whatbot(wchan->chname));
        }
    }
}

void bot_devoiceall (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan)
{
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;

    SendRaw("SVSMODE %s -v",wchan->chname);
}

void bot_opopop (Nick *nptr, User *uptr __unused, Chan *chptr __unused, Wchan *wchan)
{
    KickUser(whatbot(wchan->chname),nptr->nick,wchan->chname,"Hey, keep quiet !");
}

void bot_kick (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2;
    arg2 = all;
    all = SeperateWord(arg2);
    char *bot = whatbot(wchan->chname);
    User *uptr2;

    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') { 
        KickUser(bot,nptr->nick,wchan->chname,"Requested");
    } else {
        if (!Strcmp(arg2,whatbot(wchan->chname))) {
            KickUser(bot,nptr->nick,wchan->chname,"Don't touch !");
            return;
        }   
            
        if (!Strcmp(arg2,"*") && HasOption(chptr, COPT_MASS)) {
            Member *member,*next;
            Nick *blah;
            for (member = member_list.table[HASH(wchan->chname)]; member; member = next) {
                next = member->next;
                if (Strcmp(member->nick,nptr->nick) && !Strcmp(member->channel,wchan->chname)) {
                    blah = find_nick(member->nick);
                    if (!blah) return;
                    if (!IsOper(blah))
                        KickUser(bot,member->nick,wchan->chname,"Kicking all users");
                }
            }
            return;
        }

        uptr2 = find_user(arg2);
        if (uptr2 && IsAuthed(uptr2)) {
            if (GetFlag(uptr,chptr) < GetFlag(uptr2, chptr))
                return;
        }

        if (!all || *all == '\0')
            KickUser(bot,arg2,wchan->chname,"Requested");
        else
            KickUser(bot,arg2,wchan->chname,all);
    }
}

void bot_rkick (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2;
    arg2 = all;
    all = SeperateWord(arg2);
    char *bot = whatbot(wchan->chname);
    User *uptr2;

    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!HasOption(chptr, COPT_MASS)) return;

    if (!arg2 || *arg2 == '\0')
        KickUser(bot, nptr->nick, wchan->chname, "Requested");
    else {
        Member *member, *next;

        for (member = member_list.table[HASH(wchan->chname)]; member; member = next) {
            next = member->next;
            if (!Strcmp(member->nick, nptr->nick))
                continue;
            uptr2 = find_user(member->nick);
            if (uptr2 && IsAuthed(uptr2)) {
                if (GetFlag(uptr,chptr) < GetFlag(uptr2,chptr))
                    continue;
            }
            if (__match_regex(arg2, member->nick, REG_EXTENDED|REG_NOSUB|REG_ICASE))
                KickUser(bot, member->nick, wchan->chname, "regexp kick matching nick");
        }
    }
}

void bot_rkb (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2;
    arg2 = all;
    all = SeperateWord(arg2);
    char *bot = whatbot(wchan->chname);
    User *uptr2;

    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!HasOption(chptr, COPT_MASS)) return;

    if (!arg2 || *arg2 == '\0') {
        SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,nptr->hiddenhost);
        KickUser(bot,nptr->nick,wchan->chname,"Requested");
    } else {
        Member *member, *next;
        Nick *blah;

        for (member = member_list.table[HASH(wchan->chname)]; member; member = next) {
            next = member->next;
            if (!Strcmp(member->nick, nptr->nick))
                continue;
            if (__match_regex(arg2, member->nick, REG_EXTENDED|REG_NOSUB|REG_ICASE)) {
                blah = find_nick(member->nick);
                if (!blah) return;
                uptr2 = find_user(member->nick);
                if (uptr2 && IsAuthed(uptr2)) {
                    if (GetFlag(uptr, chptr) < GetFlag(uptr2, chptr))
                        continue;
                }
                SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,blah->hiddenhost);
                KickUser(bot, member->nick, wchan->chname, "regexp kickban matching nick");
            }
        }
    }
}

void bot_kb (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    all = SeperateWord(arg2);
    Nick *blah;
    User *uptr2;

    char *bot = whatbot(wchan->chname);

    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') {
        SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,nptr->hiddenhost);
        KickUser(bot,nptr->nick,wchan->chname,"Requested");
    } else {
        if (!Strcmp(arg2,me.nick)) {
            SendRaw(":%s MODE %s +b %s*!*@*",bot,wchan->chname,nptr->nick);
            KickUser(bot,nptr->nick,wchan->chname,"Don't touch !");
            return;
        }

        if (!Strcmp(arg2,"*") && HasOption(chptr, COPT_MASS)) {
            Member *member,*next;
            for (member = member_list.table[HASH(wchan->chname)]; member; member = next) {
                next = member->next;
                if (Strcmp(member->nick,nptr->nick) && !Strcmp(member->channel,wchan->chname)) {
                    blah = find_nick(member->nick);
                    if (!blah) return;
                    if (!IsOper(blah)) {
                        SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,blah->hiddenhost);
                        KickUser(bot,member->nick,wchan->chname,"Kickbanning all users");
                    }
                }
            }
            return;
        }

        blah = find_nick(arg2);
        if (!blah) return;

        uptr2 = find_user(arg2);
        if (uptr2 && IsAuthed(uptr2)) {
            if (GetFlag(uptr, chptr) < GetFlag(uptr2, chptr))
                return;
        }

        SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,blah->hiddenhost);
        if (!all || *all == '\0')
            KickUser(bot,arg2,wchan->chname,"Requested");
        else
            KickUser(bot,arg2,wchan->chname,all);
    }
}

void bot_unban (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    TB *tb;
    char *arg2 = all;
    SeperateWord(arg2);

    char *bot = whatbot(wchan->chname);
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') return;
    SendRaw(":%s MODE %s -b %s",bot,wchan->chname,arg2);

    tb = find_tb(chptr, arg2);
    if (tb)
        DeleteTB(tb);
}

void bot_ban (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2,*arg3;
    Nick *nptr2;
    arg2 = all;
    arg3 = SeperateWord(arg2);
    SeperateWord(arg3);

    char *bot = whatbot(wchan->chname);
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0') { 
        SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,nptr->hiddenhost);
    } else {
        nptr2 = find_nick(arg2);
        if (!nptr2) {
            SendRaw(":%s MODE %s +b %s",bot,wchan->chname,arg2);
        } else {
            if (!arg3 || *arg3 == '\0') {
                SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,nptr2->hiddenhost);
            } else {
                switch(strtol(arg3,NULL,10)) {
                    case 1:
                        SendRaw(":%s MODE %s +b %s!*@*",bot,wchan->chname,nptr2->nick);
                        break;
                    case 2:
                        SendRaw(":%s MODE %s +b *!%s@*",bot,wchan->chname,nptr2->ident);
                        break;
                    case 3:
                        SendRaw(":%s MODE %s +b *!*@%s",bot,wchan->chname,nptr2->hiddenhost);
                        break;
               }        
            }  
        }   
    }
}

void bot_topic (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_op && !IsFounder(uptr,chptr)) return;
    if (!all || *all == '\0') return;
//    SendRaw("TOPIC %s %s %ld :%s", wchan->chname, nptr->nick, time(NULL), all);
    SendRaw(":%s TOPIC %s :%s", whatbot(wchan->chname), wchan->chname, all);
}

void bot_moo (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan, char *all)
{
    char *arg2 = all;
    SeperateWord(arg2);

    if (!IsAuthed(uptr)) return;
    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;
    if (!arg2 || *arg2 == '\0')
        FakeMsg(whatbot(wchan->chname),wchan->chname,"\1ACTION m00s loudly at %s\1",nptr->nick);
    else
        FakeMsg(whatbot(wchan->chname),wchan->chname,"\1ACTION m00s loudly at %s\1",arg2);
}

void bot_seen (Nick *nptr __unused, User *uptr __unused, Chan *chptr __unused, Wchan *wchan, char *all)
{
    char *arg2;
    User *uptr2;
    Nick *nptr2;
    arg2 = all;
    SeperateWord(arg2);

    if (!arg2 || *arg2 == '\0') return;

    char *bot = whatbot(wchan->chname);

    if (!Strcmp(arg2,bot)) {
        FakeMsg(bot,wchan->chname,"I'm in a place that you will never guess !");
        return;
    }

    nptr2 = find_nick(arg2);
    uptr2 = find_user(arg2);
    if (!uptr2 && nptr2) {
        FakeMsg(bot,wchan->chname,"%s is connected but not registered", nptr2->nick);
        return;
    }

    if (!uptr2 && !nptr2) {
        FakeMsg(bot,wchan->chname,"I don't know who is %s", arg2);
        return;
    }

    if (uptr2->authed == 1) {
        FakeMsg(bot,wchan->chname,"%s is right here.", uptr2->nick);
        return;
    }

    if (uptr2->lastseen == 0) {
        FakeMsg(bot,wchan->chname,"%s is registered but I have no more information", uptr2->nick);
        return;
    }

    int timenoseen = time(NULL) - uptr2->lastseen;
    int days = timenoseen / 86400, hours = (timenoseen / 3600) % 24, mins = (timenoseen / 60) % 60, secs = timenoseen % 60;

    char hr[10];
    char mn[10];
    char sc[10];

    if (hours < 10) sprintf(hr,"0%d",hours); else sprintf(hr,"%d",hours);
    if (mins < 10) sprintf(mn,"0%d",mins); else sprintf(mn,"%d",mins);
    if (secs < 10) sprintf(sc,"0%d",secs); else sprintf(sc,"%d",secs);

    if (days > 1) {
        FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 days, \2%s:%s\2",uptr2->nick,days,hr,mn);
    } else if (days == 1) {
        FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 day, \2%s:%s\2",uptr2->nick,days,hr,mn);
    } else {
        if (hours > 1) {
            FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 hours, \2%d\2 minutes",uptr2->nick,hours,mins);
        } else if (hours == 1) {
            FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 hour, \2%d\2 minutes",uptr2->nick,hours,mins);
        } else {
            if (mins > 1) {
                FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 minutes, \2%d\2 seconds",uptr2->nick,mins,secs);
            } else if (mins == 1) {
                FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 minute, \2%d\2 seconds",uptr2->nick,mins,secs);
            } else {
                if (secs > 1) {
                    FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 seconds",uptr2->nick,secs);
                } else if (secs == 1) {
                    FakeMsg(bot,wchan->chname,"%s has not been seen for \2%d\2 second",uptr2->nick,secs);
                }
            }
        }
    }
}

void bot_admin (Nick *nptr, User *uptr __unused, Chan *chptr __unused, Wchan *wchan)
{
    User *uptr2;
    Nick *nptr2;

    char *bot = whatbot(wchan->chname);

    LIST_FOREACH_ALL(user_list, uptr2) {
        nptr2 = find_nick(uptr2->nick);
        if (nptr2 && IsOper(nptr2) && uptr2->authed == 1) {
            if (uptr2->level >= me.level_root)
                FakeNotice(bot,nptr,"%s     Oper + Services Root Administrator",uptr2->nick);
            else if (uptr2->level >= me.level_admin)
                FakeNotice(bot,nptr,"%s     Oper + Services Administrator",uptr2->nick);
            else if (uptr2->level >= me.level_oper)
                FakeNotice(bot,nptr,"%s     Oper + Services Operator",uptr2->nick);
            else
                FakeNotice(bot,nptr,"%s     Oper",uptr2->nick);
        }
    }
}

void bot_fuckall (Nick *nptr, User *uptr, Chan *chptr, Wchan *wchan)
{
    char target[2];
    strcpy(target,"*");
    bot_kick (nptr, uptr, chptr, wchan, target);
}

void bot_tb (Nick *nptr __unused, User *uptr, Chan *chptr, Wchan *wchan __unused, char *all)
{
    char *arg1, *arg2, *arg3;
    arg1 = all;
    arg2 = SeperateWord(arg1);
    arg3 = SeperateWord(arg2);
    char *mask;
    int duration = 0;
    char *tc;
    TB *tb;
    char effective_mask[256];
    char blah[256], blah2[256];
    Nick *nptr2 = NULL;
    Member *member, *next;
    User *uptr2;
    char reason[256];

    if (GetFlag(uptr,chptr) < me.chlev_halfop && !IsFounder(uptr,chptr)) return;

    if (!arg1 || *arg1 == '\0')
        return;

    mask = arg1;

    if (!arg2 || *arg2 == '\0') {
        duration = 3600;
    } else {
        if ((tc = strchr(arg2, 'm')) != NULL) {
            *tc = '\0';
            duration = atoi(arg2) * 60;
        } else if ((tc = strchr(arg2, 'h')) != NULL) {
            *tc = '\0';
            duration = atoi(arg2) * 3600;
        } else if ((tc = strchr(arg2, 'd')) != NULL) {
            *tc = '\0';
            duration = atoi(arg2) * 86400;
        } else if ((tc = strchr(arg2, 'w')) != NULL) {
            *tc = '\0';
            duration = atoi(arg2) * 86400 * 7;
        } else
            duration = atoi(arg2);
    }

    bzero(effective_mask, 256);
    if (!IsMask(mask)) {
        if ((nptr2 = find_nick(mask)) != NULL)
            snprintf(effective_mask, 256, "*!*@%s", nptr2->hiddenhost);
        else
            snprintf(effective_mask, 256, "%s!*@*", mask);
    } else
        strncpy(effective_mask, mask, 256);

    bzero(reason, 256);
    if (!arg3 || *arg3 == '\0')
        strcpy(reason, "You're banned from this channel");
    else
        strncpy(reason, arg3, 255);

    if ((tb = find_tb(chptr, effective_mask)) != NULL) {
        tb->duration = duration;
        tb->setat = time(NULL);
    } else
        tb = AddTB(chptr, effective_mask, duration, reason);

    if (nptr2) {
        if ((uptr2 = find_user(nptr2->nick)) != NULL) {
            if (IsAuthed(uptr2) && GetFlag(uptr, chptr) < GetFlag(uptr2, chptr))
                return;
        }
        KickUser(whatbot(wchan->chname), nptr2->nick, wchan->chname, reason);
    } else {
        for (member = member_list.table[HASH(wchan->chname)]; member; member = next) {
            next = member->next;
            nptr2 = find_nick(member->nick);
            bzero(blah, 256);
            bzero(blah2, 256);
            snprintf(blah, 256, "%s!%s@%s", nptr2->nick, nptr2->ident, nptr2->hiddenhost);
            snprintf(blah2, 256, "%s!%s@%s", nptr2->nick, nptr2->ident, nptr2->host);

            if ((uptr2 = find_user(member->nick)) != NULL) {
                if (IsAuthed(uptr2) && GetFlag(uptr,chptr) < GetFlag(uptr2,chptr))
                    continue;
            }

            if (match_mask(tb->mask, blah) || match_mask(tb->mask, blah2))
                KickUser(whatbot(wchan->chname), nptr2->nick, wchan->chname, reason);
        }
    }

    SendRaw(":%s MODE %s +b %s", whatbot(wchan->chname), wchan->chname, effective_mask);
}
