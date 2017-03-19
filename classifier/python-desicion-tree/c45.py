import  math

training_file_name = 'training.txt'
test_file_name = 'test.txt'
ans_field = '2'
db = None

def filter_by_cond(rows, cond):
    return [elem for elem in rows
            if set(cond.keys()) <= set(elem.keys()) and set(cond.items()) <= set(elem.items())]

def get_entropy(rows, target_field):
    entropy = 0
    ans = {}
    for r in rows:
        if r[target_field] in ans:
            ans[r[target_field]] += 1
        else:
            ans[r[target_field]] = 1
    for a in ans:
        entropy -= ans[a] / float(len(rows)) * (math.log(ans[a], 2) - math.log(float(len(rows)), 2))
    return entropy

def get_max_info_gain(rows, target_field, exclude_fields):
    if len(rows) == 0:
        return None
    result = { 'info_gain': 0, 'field': '' }
    target_field_ans_list = list(set([elem[target_field] for elem in rows]))
    for field in rows[0]:
        if field == target_field or field in exclude_fields:
            continue
        info_gain = get_entropy(rows, target_field)
        ans_set = set([elem[field] for elem in rows])
        ans_list = list(ans_set)
        for ans in ans_list:
            ans_entropy = get_entropy([elem for elem in rows if elem[field] == ans], target_field)
            info_gain -= ans_entropy * len([elem for elem in rows if elem[field] == ans]) / float(len(rows))
        if info_gain > result['info_gain']:
            result['info_gain'] = info_gain
            result['field'] = field
    return result

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

    cond_rows = db.get_rows_by_cond({})
    print(get_max_info_gain(cond_rows, '2', {}))

if __name__ == '__main__':
    main()
