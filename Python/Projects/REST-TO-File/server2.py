from flask import Flask, request, jsonify
import json

app = Flask(__name__)



# Path to the JSON file
json_file = 'data.json'

# Custom host and port
host = 'localhost'
port = 8000


def read_data():
    with open(json_file) as file:
        data = json.load(file)
    return data


def write_data(data):
    with open(json_file, 'w') as file:
        json.dump(data, file)


@app.route('/items', methods=['GET'])
def get_items():
    data = read_data()
    return jsonify(data)


@app.route('/items/<item_id>', methods=['GET'])
def get_item(item_id):
    data = read_data()
    if item_id in data:
        return jsonify(data[item_id])
    else:
        return jsonify({'error': 'Item not found'}), 404


@app.route('/items', methods=['POST'])
def create_item():
    data = read_data()
    item_id = str(max(int(key) for key in data.keys()) + 1)
    item = request.get_json()
    item['id'] = item_id
    data[item_id] = item
    write_data(data)
    return jsonify({'message': 'Item created successfully'})


@app.route('/items/<item_id>', methods=['PUT'])
def update_item(item_id):
    data = read_data()
    if item_id in data:
        item = request.get_json()
        item['id'] = item_id
        data[item_id] = item
        write_data(data)
        return jsonify({'message': 'Item updated successfully'})
    else:
        return jsonify({'error': 'Item not found'}), 404


@app.route('/items/<item_id>', methods=['DELETE'])
def delete_item(item_id):
    data = read_data()
    if item_id in data:
        del data[item_id]
        write_data(data)
        return jsonify({'message': 'Item deleted successfully'})
    else:
        return jsonify({'error': 'Item not found'}), 404
    

#add PATCH TO COMMANDS


if __name__ == '__main__':
    app.run(host=host, port=port)
