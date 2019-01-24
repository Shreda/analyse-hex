#!/usr/bin/env python3
import imaplib
import re
from pprint import pprint
from getpass import getpass

def open_connection():
    # Connect to the server
    connection = imaplib.IMAP4_SSL("imap-mail.outlook.com")
    # Read user password from stdin
    password = getpass(prompt='Password:') 
    # Connect to imap server with credentials
    connection.login("dmoore@shearwater.com.au", password)
    return connection

def print_mailboxes(connection):
    '''Prints a list of mailboxes from the IMAP server'''
    typ, data = connection.list()
    pprint(data)
    return

def read_mailbox(connection, mailbox):
    # Switch contect of connection to supplied mailbox
    typ, data = connection.select(mailbox)
    # Grab the number of emails in the mailbox from the
    # data returned by selecting the mailbox
    max = int (data[0].decode('utf-8'))
    # Itterate through the mailbox and use regex to grab
    # the generated passwords from each email
    for i in range(1, max+1):
        # Fetch the email
        ign, msg_data = connection.fetch(str(i), '(RFC822)')
        # regex the generated password
        result = re.search(r"<code>[A-F0-9]{6}", msg_data[0][1].decode('utf-8'))
        hexcode = re.search(r"[A-F0-9]{6}", result.group(0))
        # print the generated password to the stdout
        print(hexcode.group(0))

if __name__ == '__main__':
    # Set up connection to server
    imap_connection = open_connection()
    # Read emails from specific mailbox
    read_mailbox(imap_connection, "2019/Hollard/SEH1451/support_emails")

