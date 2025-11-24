from collections import defaultdict

from docutils import nodes
from sphinx import addnodes
from docutils.parsers.rst import Directive, directives
from sphinx.directives import ObjectDescription
from sphinx.domains import Domain, Index
from sphinx.roles import XRefRole
from sphinx.util.nodes import make_refnode

from sphinx.application import Sphinx
from docutils import nodes

class Requirement(ObjectDescription):
    has_content = True
    required_arguments = 1
    optional_arguments = 2
    option_spec = {'rationale': directives.unchanged, 'derivedfrom': directives.unchanged}

    def handle_signature(self, sig, signode):
        signode += addnodes.desc_name(text=sig)
        return sig

    def add_target_and_index(self, name_cls, sig, signode):
        signode['ids'].append('req' + '-' + sig)
        domain = self.env.get_domain('req')
        domain.add_requirement(self.arguments[0])

    def run(self):
        super().run()

        table = nodes.table(cols=2, width="100%", classes=["colwidths-given"])
        group = nodes.tgroup()
        head = nodes.thead()
        body = nodes.tbody()

        group += nodes.colspec(colwidth=20)
        group += nodes.colspec(colwidth=80)
        table += group
        group += head
        group += body

        row = nodes.row()
        row += nodes.entry('', nodes.strong('', nodes.Text('ID')))
        row += nodes.entry('', nodes.paragraph('', nodes.Text(self.arguments[0])))
        body += row

        row = nodes.row()
        row += nodes.entry('', nodes.strong('', nodes.Text('Description')))
        row += nodes.entry('', nodes.paragraph('', nodes.Text("".join(self.content))))
        body += row

        if "rationale" in self.options:
            row = nodes.row()
            row += nodes.entry('', nodes.strong('', nodes.Text('Rationale')))
            row += nodes.entry('', nodes.paragraph('', nodes.Text(self.options["rationale"])))
            body += row

        if "derivedfrom" in self.options:
            derivedfrom_list = self.options['derivedfrom'].split(',')
            row = nodes.row()
            row += nodes.entry('', nodes.strong('', nodes.Text('Derived from')))
            derivedfrom_entry = nodes.entry()
            for derivedfrom in derivedfrom_list:
                derivedfrom = derivedfrom.strip()

                if len(derivedfrom) > 0:
                    ref_node = addnodes.pending_xref(
                        "", 
                        nodes.literal('', 
                            f"{derivedfrom}",
                            classes=["xref", "req", "req-ref"]
                        ),
                        refdoc=self.env.docname,
                        refdomain="req",
                        refexplicit=False,
                        reftype='ref',
                        reftarget=derivedfrom,
                        refwarn=True,
                    )
                    p = nodes.paragraph()
                    p += ref_node
                    derivedfrom_entry += p
            row += derivedfrom_entry
            body += row
            

        return [table]

class RequirementIndex(Index):
    name = 'requirement'
    localname = 'Requirement Index'
    shortname = 'Requirement'

    def generate(self, docnames=None):
        content = defaultdict(list)

        # sort the list of recipes in alphabetical order
        requirements = self.domain.get_objects()
        requirements = sorted(requirements, key=lambda requirement: requirement[0])

        # generate the expected output, shown below, from the above using the
        # first letter of the requirement as a key to group thing
        #
        # name, subtype, docname, anchor, extra, qualifier, description
        for _name, dispname, typ, docname, anchor, _priority in requirements:
            content[dispname[0]].append((
                dispname,
                0,
                docname,
                anchor,
                docname,
                '',
                '',
            ))

        # convert the dict to the sorted list of tuples expected
        content = sorted(content.items())

        return content, True

class RequirementDomain(Domain):
    name = 'req'
    label = 'Requirement'
    roles = {
        'ref': XRefRole(),
    }
    indices = {
        RequirementIndex
    }
    initial_data = {
        'requirements': []
    }

    def get_objects(self):
        yield from self.data['requirements']

    def resolve_xref(self, env, fromdocname, builder, typ, target, node, contnode):
        match = [
            (docname, anchor)
            for name, sig, typ, docname, anchor, prio in self.get_objects()
            if sig == target
        ]

        if len(match) > 0:
            todocname = match[0][0]
            targ = match[0][1]

            return make_refnode(builder, fromdocname, todocname, targ, contnode, targ)
        else:
            return None

    def add_requirement(self, signature):
        name = f'req.{signature}'
        anchor = f'req-{signature}'
        self.data['requirements'].append((name, signature, 'Requirement', self.env.docname, anchor, 0))

def setup(app: Sphinx):
    app.add_directive('requirement', Requirement)
    app.add_domain(RequirementDomain)

    return {
        'version': '0.1',
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }
