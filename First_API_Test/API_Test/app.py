from flask import Flask, jsonify, request, render_template, url_for, redirect
from members import members_api, members                                             # Import Blueprint + Liste


app = Flask(__name__)
app.register_blueprint(members_api)

@app.route("/")  # http://127.0.0.1:5000
def home():                                                                            
    return render_template('home.html')

@app.route('/members-html') 
def show_members():
    return render_template('members.html', members=members) # 'members=members' links: Variable in HTML; rechts: Variable aus PY

@app.route('/add-Member', methods=['GET']) 
def show_add_form():
    return render_template('addMember.html')

@app.route("/members/<string:name>/")  
def getMember(name):                                                                   
    return name

@app.route('/delete-member/<int:member_id>', methods=['POST'])
def delete_member(member_id):
    global members 
    members = [m for m in members if m['id'] != member_id]
    return redirect(url_for('show_members'))

if __name__ == "__main__":
    app.run(debug=True)
