from flask import Flask, jsonify, request, render_template
from members import members_api, members                                             # Import Blueprint + Liste


app = Flask(__name__)
app.register_blueprint(members_api)

@app.route("/")  # http://127.0.0.1:5000
def home():                                                                            
    return render_template('home.html')

@app.route('/members-html') # http://127.0.0.1:5000/members-html
def show_members():
    return render_template('members.html', members=members) # 'members=members' links: Variable in HTML; rechts: Variable aus PY

@app.route('/add-Member', methods=['GET']) # http://127.0.0.1:5000/add-Member
def show_add_form():
    return render_template('addMember.html')

@app.route("/members/<string:name>/")  # http://127.0.0.1:5000/members/Alice/
def getMember(name):                                                                   
    return name

if __name__ == "__main__":
    app.run(debug=True)