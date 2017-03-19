import  math

training_file_name = 'training.txt'
test_file_name = 'test.txt'
ans_field = '2'
db = None

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

def get_info_gain(rows, target_field, exclude_fields):
    if len(rows) == 0:
        return None
    info_gain = get_entropy(rows, target_field)
    fields = {}
    for field in rows[0]:
        if field == target_field or field in exclude_fields:
            continue
        fields[field] = {'total': 0, 'condition': {}}
    for r in rows:
        for field in r:
            fields[field]['total'] += 1
            if r[target_field] in fields[field]['condition']:
                fields[field]['condition'][r[target_field]] += 1
            else:
                fields[field]['condition'][r[target_field]] = 1
    print(fields)


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

    # def get_max_info_gain_ratio(self, cond, target_field):
    #     cond_rows = self.get_rows_by_cond(cond)
    #     target_field_ans = set([elem[target_field] for elem in cond_rows])
    #     total_entropy = FieldSelector().get_entropy(cond_rows, target_field)
    #     max_gain_ratio_field = None
    #     max_gain_ratio = 0
    #     for field in self.fields:
    #         if field in cond.keys() or field == target_field:
    #             continue
    #         field_ans = {}
    #         total_sub_entropy = 0
    #         info_gain = total_entropy
    #         for row in cond_rows:
    #             if row[field] in field_ans:
    #                 field_ans[row[field]]['total'] += 1
    #                 if row[target_field] not in field_ans[row[field]]['condition']:
    #                     field_ans[row[field]]['condition'][row[target_field]] = 1
    #                 else:
    #                     field_ans[row[field]]['condition'][row[target_field]] += 1
    #             else:
    #                 field_ans[row[field]] = { 'total': 1, 'condition': {} }
    #                 field_ans[row[field]]['condition'][row[target_field]] = 1
    #         for ans in field_ans:
    #             print('ans:' + ans)
    #             for target_ans in field_ans[ans]['condition']:
    #                 total_sub_entropy -= (field_ans[ans]['condition'][target_ans] / float(field_ans[ans]['total'])) * (math.log(field_ans[ans]['condition'][target_ans], 2) - math.log(field_ans[ans]['total'], 2))
    #             info_gain -= total_sub_entropy * field_ans[ans]['total'] / float(len(cond_rows))
    #         print(info_gain)
    #         break
    #

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
    print(get_entropy(cond_rows, '2'))

if __name__ == '__main__':
    main()
