import  math

training_file_name = 'training.txt'
test_file_name = 'test.txt'
ans_field = '2'
db = None

class Database:

    def __init__(self, raw_data_list):
        self.db = []
        self.fields = set()
        self.data_list = raw_data_list
        for elem in self.data_list:
            row = {}
            for cell in elem.replace('{', '').replace('}', '').split(','):
                key = cell.split(' ')[0]
                value = cell.split(' ')[1]
                row[key] = value
                self.fields.add(key)
            if '2' not in row:
                row['2'] = 'Basic'
            self.db.append(row)
        for elem in self.db:
            for field in self.fields:
                if field not in elem:
                    elem[field] = 'unknown'

    def info(self):
        print('len: ' + str(len(self.db)) + ', fields: ' + str(self.fields))

    def get_row(self, index):
        return self.db[index] if len(self.db) > index and index >= 0 else None

    def get_fields(self):
        return self.fields

    def get_cell(self, index, field):
        return self.db[index][field] if field in self.db[index] else 'unknown'

    def get_rows_by_cond(self, cond):
        return [elem for elem in self.db
                if set(cond.keys()) <= set(elem.keys()) and set(cond.items()) <= set(elem.items())]

    def get_max_info_gain_ratio(self, cond, target_field):
        cond_rows = self.get_rows_by_cond(cond)
        target_field_cond = set([elem[target_field] for elem in cond_rows])
        total_entropy = 0
        for ans in target_field_cond:
            count = len([elem for elem in cond_rows if elem[target_field] == ans])
            total_entropy -= (count / float(len(cond_rows))) * (math.log(count, 2) - math.log(len(cond_rows), 2))

class DesicionTreeNode:

    def __init__(self, node_name):
        self.field = node_name
        self.children_node = {}

    def add_child(self, ans, node):
        if ans not in self.children_node:
            self.children_node[ans] = node

    def get_child(self, ans):
        return self.children_node[ans] if ans in self.children_node else None

    def get_name(self):
        return self.field

def main():
    with open(training_file_name) as f:
        raw_data = [elem.rstrip('\n') for elem in f.readlines()]
        db = Database(raw_data)

    db.get_max_info_gain_ratio({}, ans_field)

if __name__ == '__main__':
    main()
