
import os
import numpy as np
from lxml import etree


def writeTableRST(file_name, values):
  L = [[len(x) for x in row] for row in values]
  M = tuple(np.amax(np.array(L), axis=0))

  # Build column formats (the final column is allowed to use multiple lines)
  single_row_format = ('{:<%is} ' * len(M) + '\n') % M

  # The final column is allowed to span multiple lines
  description_index = sum(M[:-1]) + len(M) - 1
  multiple_row_format_a = ('{:<%is} ' * (len(M) - 1) + '| {:<%is} \n') % M
  multiple_row_format_b = ' ' * description_index + '| {:<%is} \n' % (M[-1])

  # Build headers
  boundary = single_row_format.format(*['=' * x for x in M])

  # Format lines
  formatted_lines = []
  for ii in range(0, len(values)):
    if ('\\n' not in values[ii][-1]):
      # Single line entry
      formatted_lines.append(single_row_format.format(*values[ii]))

    else:
      # Multi-line entry
      description = values[ii][-1].split('\\n')
      values[ii][-1] = description[0]
      formatted_lines.append(multiple_row_format_a.format(*values[ii]))

      for d in description[1:]:
        formatted_lines.append(multiple_row_format_b.format(d))

  # Build table
  with open(file_name, 'w') as f:
    f.write('\n\n')
    f.write(boundary)
    f.write(formatted_lines[0])
    f.write(boundary)
    for line in formatted_lines[1:]:
      f.write(line)
    f.write(boundary)
    f.write('\n\n')


# Config
input_name = 'schema.xsd'
complete_output = '../../../docs/sphinx/CompleteXMLSchema'
output_folder = 'docs'
sphinx_path = '../../coreComponents/fileIO/schema/docs'
xsd = '{http://www.w3.org/2001/XMLSchema}'


# Parse schema, build docs
os.system('mkdir -p %s' % (output_folder))

include_tree = etree.parse(input_name)
include_root = include_tree.getroot()

with open('%s.rst' % (complete_output), 'w') as output_handle:
  output_handle.write('======================\n')
  output_handle.write('Complete XML Structure\n')
  output_handle.write('======================\n\n')
  output_handle.write('********************************\n')
  output_handle.write('Autogenerated Schema Definitions\n')
  output_handle.write('********************************\n\n')

  for child_node in include_root.findall(xsd + 'complexType'):
    type_name = child_node.get('name')[:-4]
    table_values = [['Name', 'Type', 'Default', 'Description']]

    # Parse comments
    attribute_comments = {}
    for comment_node in child_node.iterchildren(etree.Comment):
      tmp = str(comment_node)[4:-3].split(' = ', 1)
      attribute_comments[tmp[0]] = tmp[1].replace('\\\\', '\\').replace('\n', '\\n')

    # Parse attributes
    for attribute_node in child_node.findall(xsd + 'attribute'):
      table_row = [attribute_node.get(v, default=' ') for v in ['name', 'type', 'default']]
      useValue = attribute_node.get('use')
      if useValue:
        table_row[2] = useValue

      table_values.append(table_row)

      k = table_values[-1][0]
      if k in attribute_comments:
        table_values[-1].append(attribute_comments[k])
      else:
        table_values[-1].append(' ')

    # Parse nodes
    for choice_node in child_node.findall(xsd + 'choice'):
      for sub_node in choice_node.findall(xsd + 'element'):
        sub_name = sub_node.get('name')
        sub_required = sub_node.get('minOccurs')
        sub_unique = sub_node.get('maxOccurs')
        node_use = ''
        if sub_required:
          if sub_unique:
            node_use = 'unique, required'
          else:
            node_use = 'required'
        elif (sub_unique):
          node_use = 'unique'

        table_values.append([sub_name, 'node', node_use, ':ref:`XML_%s`' % (sub_name)])

    # Write table
    writeTableRST('%s/%s.rst' % (output_folder, type_name), table_values)

    element_header = 'Element: %s' % (type_name)
    output_handle.write('\n.. _XML_%s:\n\n' % (type_name))
    output_handle.write('%s\n' % (element_header))
    output_handle.write('='*len(element_header) + '\n')
    output_handle.write('.. include:: %s/%s.rst\n\n' % (sphinx_path, type_name))
