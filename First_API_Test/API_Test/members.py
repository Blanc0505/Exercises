from flask import Blueprint, jsonify, request, redirect, url_for

members_api = Blueprint('members_api', __name__) 

members = [                                                 # Liste mit Dictionarys 
    {"id": 1, "name": "Jason"},
    {"id": 2, "name": "Derulo"},
    {"id": 3, "name": "Max"},
    {"id": 4, "name": "Melmeth"},
    {"id": 5, "name": "Gert"},
    {"id": 6, "name": "Jar-Jar"},
    {"id": 7, "name": "Anakin"},
    {"id": 8, "name": "Finja"}
]

@members_api.route('/members', methods=['GET'])             # GET-Endpunkt 
def get_members():
    return jsonify(members)

@members_api.route('/addMember', methods=['POST'])            # Post-Anfrage zum Hinzufügen von Mitgliedern 
def add_member_from():
    name = request.form['name']
    new_id = max((m['id'] for m in members), default=0) + 1
    new_member = {"id": new_id, "name": name}
    members.append(new_member)
    return redirect(url_for('show_members'))                   # weiterleiten zur member list               
