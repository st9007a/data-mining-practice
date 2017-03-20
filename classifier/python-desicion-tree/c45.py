import  math

training_file_name = 'training.txt'
test_file_name = 'test.txt'
output_file_name = 'output.txt'
ans_field = '2'

global db
db = None

class Database:

    def __init__(self, raw_data_list):
        self.iterator_pointer = 0
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
            if '3' in row:
                row['3'] = self.parse_age(row['3'])
            self.db.append(row)
        for elem in self.db:
            for field in self.fields:
                if field not in elem:
                    elem[field] = 'unknown'

    def parse_age(self, age):
        return str(int(age) / 10)

    def get_rows_by_cond(self, cond):
        return [elem for elem in self.db
                if set(cond.keys()) <= set(elem.keys()) and set(cond.items()) <= set(elem.items())]

    def get_fields(self):
        return self.fields

    def get_row(self, index):
        if index >= len(self.db) or index < 0:
            return None
        return self.db[index]

    def __iter__(self):
        return self

    def next(self):
        if self.iterator_pointer >= len(self.db):
            raise StopIteration
        self.iterator_pointer += 1
        return self.db[self.iterator_pointer - 1]

class DesicionTreeNode:

    def __init__(self):
        self.children_node = {}
        self.answer = {}
        self.is_answer = False
        self.field_name = ''

    def add_child(self, ans, node):
        if ans not in self.children_node:
            self.children_node[ans] = node

    def set_field_name(self, field_name):
        self.field_name = field_name

    def set_answer(self, ans, percent):
        self.answer[ans] = percent
        self.is_answer = True

    def get_child(self, ans):
        return self.children_node[ans] if ans in self.children_node else None

    def get_field_name(self):
        return self.field_name

    def chk_is_answer(self):
        return self.is_answer

    def get_answer(self):
        return self.answer

    def get_field_answer(self):
        return self.children_node.keys()

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
        if info_gain >= result['info_gain']:
            result['info_gain'] = info_gain
            result['field'] = field
    return result

def build_d_tree(node, target_field, cond):
    global db
    rows = db.get_rows_by_cond(cond)
    if len(cond.keys()) + 1 == len(db.get_fields()):
        target_field_ans = set([elem[target_field] for elem in rows])
        for ans in target_field_ans:
            node.set_answer(ans, len([elem for elem in rows if elem[target_field] == ans]) / float(len(rows)))
        return node
    elif len(set([elem[target_field] for elem in rows])) == 1:
        node.set_answer(rows[0][target_field], 1)
        return node
    field = get_max_info_gain(rows, target_field, cond)['field']
    node.set_field_name(field)
    field_ans = set([elem[field] for elem in rows])
    new_cond = dict(cond)
    for ans in field_ans:
        new_cond[field] = ans
        node.add_child(ans, build_d_tree(DesicionTreeNode(), target_field, new_cond))
    return node

def match_d_tree(node, data):
    if node.chk_is_answer():
        return node.get_answer()
    if node.get_child(data[node.get_field_name()]) == None:
        return None
    return match_d_tree(node.get_child(data[node.get_field_name()]), data)

def tree_info(node):
    if node.chk_is_answer():
        print 'answer: ' + str(node.get_answer())
        return
    print 'field: ' + node.get_field_name()
    for ans in node.get_field_answer():
        print 'ans: ' + ans
        tree_info(node.get_child(ans))

def main():

    print 'read training data ...'
    with open(training_file_name) as training_file:
        raw_data = [elem.rstrip('\n') for elem in training_file.readlines()]
        global db
        db = Database(raw_data)

    print 'build tree model ...'
    d_tree = DesicionTreeNode()
    d_tree = build_d_tree(d_tree, ans_field, {})

    # tree_info(d_tree)
    print 'run test data ...'
    with open(test_file_name) as test_file, open(output_file_name, 'w+') as output_file:
        raw_data = [elem.rstrip('\n') for elem in test_file.readlines()]
        test_db = Database(raw_data)
        i = 0
        for data in test_db:
            result = match_d_tree(d_tree, data)
            output_str = raw_data[i]
            output_str += ' member_card = '
            if result != None:
                for res in result:
                    output_str += res + ': ' + str(result[res] * 100) + '%,'
            else:
                output_str += 'unknown'
            output_str += '\n'
            # print output_str
            i += 1
            output_file.write(output_str)

if __name__ == '__main__':
    main()
