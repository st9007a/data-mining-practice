import  math

training_file_name = 'training.txt'
test_file_name = 'test.txt'
ans_field = '2'

global db
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

    def get_rows_by_cond(self, cond):
        return [elem for elem in self.db
                if set(cond.keys()) <= set(elem.keys()) and set(cond.items()) <= set(elem.items())]

class DesicionTreeNode:

    def __init__(self):
        self.children_node = {}
        self.answer = None

    def add_child(self, ans, node):
        if ans not in self.children_node:
            self.children_node[ans] = node

    def set_field_name(self, field_name):
        self.field_name = field_name

    def set_ans(self, ans):
        self.answer = ans

    def get_child(self, ans):
        return self.children_node[ans] if ans in self.children_node else None

    def get_name(self):
        return self.field

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
    for field in rows[0]:
        if field == target_field or field in exclude_fields:
            continue
        info_gain = get_entropy(rows, target_field)
        ans_set = set([elem[field] for elem in rows])
        ans_list = list(ans_set)
        for ans in ans_list:
            rows_have_ans = [elem for elem in rows if elem[field] == ans]
            ans_entropy = get_entropy(rows_have_ans, target_field)
            info_gain -= ans_entropy * len(rows_have_ans) / float(len(rows))
        if info_gain > result['info_gain']:
            result['info_gain'] = info_gain
            result['field'] = field
    return result

def build_d_tree(node, target_field, cond):
    global db
    rows_by_cond = db.get_rows_by_cond(cond)
    if len(list(set([elem[target_field] for elem in rows_by_cond]))) == 1:
        node.set_answer(rows_by_cond[0][target_field])
        return node
    field = get_max_info_gain(rows_by_cond, target_field, cond)['field']
    node.set_field_name = field
    # find field answer
    field_ans = set([elem[field] for elem in rows_by_cond])
    for ans in field_ans:
        cond[field] = ans
        node.add_child(build_d_tree(DesicionTreeNode(), target_field, cond))
    return node

def main():

    with open(training_file_name) as f:
        raw_data = [elem.rstrip('\n') for elem in f.readlines()]
        global db
        db = Database(raw_data)
    d_tree = DesicionTreeNode()
    d_tree = build_d_tree(d_tree, ans_field, {})

if __name__ == '__main__':
    main()
