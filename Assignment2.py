"""
   Assignment 2_01_Team15
   Jiaming Tian 35708557
   Xianlong Huang 36203335
   Tianqi Wang  35943513
   Yicheng Zhi 35013842
"""

import fileinput
from Assignment1Part3_Template.DriverProgram import display_menu

class SupportTicket:
    def __init__(self, ticket_id, title, description, status, staff, critical_status, type):
        self.ticket_id = ticket_id
        self.title = title
        self.description = description
        self.status = status
        self.staff = staff
        self.critical_status = critical_status
        self.type = type

    def get_ticket_id(self):
        return self.ticket_id
    def get_title(self):
        return self.title
    def get_description(self):
        return self.descriptions
    def get_status(self):
        return self.status
    def get_staff(self):
        return self.staff
    def get_critical_status(self):
        return self.critical_status
    def get_type(self):
        return self.type

    def set_ticket_id(self,new_ticket_id):
        self.ticket_id=new_ticket_id
    def set_title(self,new_title):
        self.title=new_title
    def set_description(self,new_description):
        self.description=new_description
    def set_status(self,new_status):
        self.status=new_status
    def set_staff(self,new_staff):
        self.staff=new_staff
    def set_critical_status(self,new_critical_status):
        self.critical_status=new_critical_status
    def set_type(self,new_type):
        self.type=new_type

    def add_new_ticket(self):
        self.ticket_id = input("Enter Ticket ID:")
        self.title = input("Enter Ticket title:")
        self.descriptions = input("Enter Ticket descriptions:")
        self.status = input("Enter status 1.(Open), 2.(Closed), 3.(InProgress)")
        self.staff = input("assigned by ['Technician 1','Technician 2','Technician 3''Technician 4','Technician 5']:")
        self.critical_status = input("Enter Critical Status (1 (Critical), 2 (Non-Critical)")
        self.type = input("Enter type(1.Hardware or 2.Software):")

        if not self.ticket_id.isdigit():  #check the ticket_id should be number
            print("The ticket ID should be a number")
            return

        ticket_exists = False
        with open("tickets.txt", "r") as t:
            lines = t.readlines()
            for line in lines:
                if f"ID:{self.ticket_id}" in line:
                    ticket_exists = True
                    break

        if ticket_exists:
            print("This ticket already exists!")
        else:
            with open("tickets.txt", "a") as addfile:
                tickets_line = f"ID:{self.ticket_id}, Title:{self.title}, Description:{self.descriptions}, Status:{self.status}, Staff:{self.staff}, Critical_Status:{self.critical_status}, Type:{self.type}\n"
                addfile.write(tickets_line)
                print("-------------------------")
                print("Ticket added successfully.")

        if self.status == "1":
            self.status = "Open"
        elif self.status == "2":
            self.status = "Closed"
        elif self.status == "3":
            self.status = "InProgress"
        else:
            print("Invalid status.")
            return

        if self.type == "1":
            self.type = "Hardware"
            print("Choose from: Technician 1, Technician 2, Technician 3")
        elif self.type == "2":
            self.type = "Software"
            print("Choose from: Technician 4, Technician 5")
        else:
            print("Invalid ticket type.")
            return

        if self.critical_status == "1":
            self.critical_status = "Critical"
        elif self.critical_status == "2":
            self.critical_status = "Non-Critical"
        else:
            print("Invalid critical status.")
            return

        if self.type == "Hardware":
            if hardware_techs[self.staff] > max_handle:
                print("Technician invalid or full.")
                return
            hardware_techs[self.staff] += 1
        elif self.type == "Software":
            if software_techs[self.staff] > max_handle:
                print("Technician invalid or full.")
                return
            software_techs[self.staff] += 1

    def view_all_tickets(self):
        with open("tickets.txt", "r") as viewfile:
            lines = viewfile.readlines()
            for ticket in lines:
                print(ticket)

    def update_ticket_status(self):
        ticket_id = input("Enter Ticket ID: ")
        new_status = input("Enter New Status (Open, Closed, InProgress): ")

        with open("tickets.txt", "r") as updatefile:
            lines = updatefile.readlines()
            for ticket in tickets:
                if str(ticket.ticket_id) == ticket_id:
                    ticket.status = new_status
                    print("Status updated successfully.")
                    break

            print("Updated Tickets:")
            for ticket in tickets:
                print("ID:", ticket.ticket_id, "Status:", ticket.status)

    def delete_ticket(self):
        delete_ticket_id = input("Please enter the Ticket ID you want to remove: ")

        with open("tickets.txt", "r") as delete_ticket_file:
            lines = delete_ticket_file.readlines()

        updated_lines = []
        found = False
        for ticket in lines:
            if f"ID:{delete_ticket_id}" not in lines:
                updated_lines.append(lines)
            else:
                found = True

        with open("tickets.txt", "w") as delete_ticket_file:
            lines =delete_ticket_file.writelines()

        if found:
            print("Ticket deleted successfully.")
        else:
            print("Ticket not found")

    def search_ticket_by_id(self):
        search_id = input("Enter the Ticket ID to search: ")
        found = False
        with open("tickets.txt", "r") as search_id_file:
            for ticket in search_id_file:
                if f"ID:{search_id}" in ticket:
                    print("Ticket Found:",ticket)
                    found = True
                    break
        if not found:
            print("Ticket not found")

    def view_tickets_by_type(self):
        user_input = input("Enter type (Hardware/Software): ")
        found = False
        with open("tickets.txt", "r") as typefile:
            for ticket in typefile:
                if f"Type:{user_input}" in ticket:
                    print("Type",ticket)
                    found = True
        if not found:
            print("No tickets of that type.")

    def view_tickets_by_critical_status(self):
        user_input = input("Enter critical status (Critical/Non-Critical):")
        found = False
        with open("tickets.txt", "r") as criticalfiles:
            for ticket in criticalfiles:
                if f"Critical_Status:{user_input}" in ticket:
                    found = True
        if not found:
            print("No tickets with that critical status.")

    def view_tickets_by_staff(self):
        user_input = input("Enter technician name:")
        found = False
        with open("tickets.txt", "r") as staff_file:
            for ticket in staff_file:
                if f"Staff:{user_input}" in ticket:
                    found = True
        if not found:
            print("This technician has no tickets.")

hardware_techs = {"Technician 1":0, "Technician 2":0, "Technician 3":0}
software_techs = {"Technician 4":0, "Technician 5":0}
max_handle = 5
tickets = []

ticket_table = SupportTicket(0, "", "", 0, "", 0, 0)

def main_menu():
    while True:
        print("1. Add New Ticket")
        print("2. View All Tickets")
        print("3. Update Ticket Status")
        print("4. Delete Ticket")
        print("5. Search Ticket by ID")
        print("6. View Tickets by Type")
        print("7. View Tickets by Critical Status")
        print("8. View Tickets by Staff")
        print("9. Save Changes and Exit")
        choice = input("Enter choice (1-9): ")

        if choice == "1":
            ticket_table.add_new_ticket()
        elif choice == "2":
            ticket_table.view_all_tickets()
        elif choice == "3":
            ticket_table.update_ticket_status()
        elif choice == "4":
            ticket_table.delete_ticket()
        elif choice == "5":
            ticket_table.search_ticket_by_id()
        elif choice == "6":
            ticket_table.view_tickets_by_type()
        elif choice == "7":
            ticket_table.view_tickets_by_critical_status()
        elif choice == "8":
            ticket_table.view_tickets_by_staff()
        elif choice == "9":
            print("Change saved. Exiting program.")
            break
        else:
            print("Invalid choice.")

main_menu()

class SoftwareTicket(SupportTicket):
    def __init__(self, ticket_id, title, description, status, staff,critical_status,type,new_software_name):
        super().__init__(ticket_id, title, description, status, staff, critical_status,type)
        self.software_name = new_software_name

    def get_software_name(self):
        return self.software_name

    def set_software_name(self, new_software_name):
        self.software_name = new_software_name



class HardwareTicket(SupportTicket):
    def __init__(self, ticket_id, title, description, status, staff,critical_status,type,new_hardware_name):
        super().__init__(ticket_id, title, description, status, staff, critical_status,type)
        self.hardware_name = new_hardware_name

    def get_hardware_name(self):
        return self.hardware_name

    def set_hardware_name(self, new_hardware_name):
        self.hardware_name = new_hardware_name
