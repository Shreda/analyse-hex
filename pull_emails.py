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
    typ, data = connection.list()
    pprint(data)
    return

def read_mailbox(connection, mailbox):
    typ, data = connection.select(mailbox)
    max = int (data[0].decode('utf-8'))
    for i in range(1, max+1):
        ign, msg_data = connection.fetch(str(i), '(RFC822)')
        result = re.search(r"<code>[A-F0-9]{6}", msg_data[0][1].decode('utf-8'))
        hexcode = re.search(r"[A-F0-9]{6}", result.group(0))
        print(hexcode.group(0))

if __name__ == '__main__':
    # Set up connection to server
    imap_connection = open_connection()
    # Read emails from specific mailbox
    read_mailbox(imap_connection, "2019/Hollard/SEH1451/support_emails")

